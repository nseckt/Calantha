/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

.code32

.extern kernel_init
.type kernel_init, @function


/* Page table entry flags */
.set PAGE_PRESENT,  (1 << 0)
.set PAGE_WRITABLE, (1 << 1)
.set PAGE_USER,     (1 << 2)
.set PAGE_HUGE,     (1 << 7)

/* Initial kernel stack */
.section .stack, "aw", @nobits
stack_bottom:
.skip 16384
stack_top:

/* Boot page table structures */
.section .page_tables, "aw", @nobits
.align 4096

.global boot_pml4
boot_pml4:
.skip 4096

.global boot_pdpt
boot_pdpt:
.skip 4096

.global boot_pd
boot_pd:
.skip 4096

/* Global Descriptor Table (GDT) */
.section .data
gdt_start:
.quad 0
gdt64_code:
.quad (1<<43) | (1<<44) | (1<<47) | (1<<53)
.global gdt_ptr
gdt_ptr:
.short . - gdt_start - 1
.quad gdt_start

.set CODE64_SELECTOR_OFFSET, gdt64_code - gdt_start


.section .text
.global _start
.type _start @function
_start:
    movl $stack_top, %esp     ## set up a small initial stack.
                              ##
    call check_multiboot

    pushfl
    movl (%esp), %edx         ## Save EFLAGS state
    popfl                     ##

    call check_cpuid          ## Ensure that the CPUID instruction is available.
                              ##
    pushfl
    movl (%esp), %ecx
    popfl

    cmpl %ecx, %edx           ## Perform sanity check:
    jne halt                  ## Ensure that the flags register has been restored correctly.

    call check_cpuid_ext
    call check_longmode
    call check_large_pages
    call init_page_tables
    call enable_paging

    movl $stack_top, %esp     ## Reset stack pointer.
    andl $-16, %esp           ## 16-byte align the stack to conform to the sysV ABI.

    mov $gdt_ptr, %eax        ## Load the GDT, perform long jump to enter 64 bit.
    lgdt (%eax)
    ljmpl $CODE64_SELECTOR_OFFSET, $long_mode_start

halt:                         ## if this is ever reached, something's probably gone wrong.
    cli                       ## clear interrupt flag.
1:                            ## spin forever.
    hlt                       ##
    jmp 1b

check_multiboot:
    cmpl $0x36D76289, %eax    ## Check for multiboot2 magic value in eax.
    jne halt                  ## If we havent't been loaded by a multiboot2 bootloader, hcf.
    ret                       ##

check_cpuid:
    pushfl                    ## save flags register.
    pushfl                    ## get current value for modification purposes.
    movl (%esp), %ecx
    xorl $0x00200000, %ecx    ## Flip bit 21 (CPUID bit).
    movl %ecx, (%esp)         ##
    popfl                     ## Attempt to modify the CPUID bit.
    pushfl                    ##
    popl %eax
    movl (%esp), %ecx
    cmpl %eax, %ecx           ## Check if the flags register has been modifed
    je halt                   ## If the registers are identical, hcf.
    popfl                     ## Restore original EFLAGS state
    ret                       ##

check_cpuid_ext:              ##
    movl $0x80000000, %eax    ## Check if CPUID extended functions are available.
    cpuid
    cmpl $0x80000001, %eax
    jb halt
    ret
                              ##
check_longmode:               ## Check if longmode is supported via CPUID.
    movl $0x80000001, %eax
    cpuid
    testl $(1 << 29), %edx
    jz halt
    ret

check_large_pages:
    xorl %edx, %edx
    movl $1, %eax
    cpuid
    testl $(1<<3), %edx
    jz halt
    ret
                              ##
init_page_tables:             ## Initialize boot page tables for identity mapping.
    movl $boot_pdpt, %eax
    movl $boot_pml4, %ecx
    orl $(PAGE_PRESENT | PAGE_WRITABLE), %eax
    movl %eax, (%ecx)

    movl $boot_pd, %eax
    movl $boot_pdpt, %ecx
    orl $(PAGE_PRESENT | PAGE_WRITABLE), %eax
    movl %eax, (%ecx)
                              ##
    movl $0, %ecx             ## ecx = loop counter
    movl $boot_pd, %ebx       ## ebx = page directory begin
.loop:
    movl $0x200000, %eax
    mull %ecx
    orl $(PAGE_PRESENT | PAGE_WRITABLE | PAGE_HUGE), %eax
    movl %eax, (%ebx, %ecx, 8)

    incl %ecx
    cmpl $512, %ecx
    jne .loop

    ret

enable_paging:
    mov $boot_pml4, %eax      ##
    mov %eax, %cr3            ## Pass PML4 location to the CPU

    movl %cr4, %eax
    orl $(1<<5), %eax         ##
    movl %eax, %cr4           ## Enable PAE (Physical Address Extension)

    movl $0xC0000080, %ecx    ## Ask for EFER MSR (magic=0xC0000080)
    rdmsr                     ## eax and edx now contain the upper and lower 32 bits of IA32_EFER.
    orl $(1<<8), %eax         ## Enable long mode bit in eax.
    wrmsr                     ## Write the new value back into the IA32_EFER register to enable long mode.

    movl %cr0, %eax           ## Read control register 0 (CR0)
    orl $(1<<31), %eax        ## Set bit 31 (page enable bit)
    movl %eax, %cr0           ## Store new value.

    ret

.code64                       ##
long_mode_start:              ## Start of 64 bit execution.
    mov $0, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    #movl $0x2f4b2f4f, (0xb8000)
    call reload_cr3
    call kernel_init

    cli
1:
    hlt
    jmp 1b

reload_cr3:
    pushq %rax
    mov %cr3, %rax
    mov %rax, %cr3
    popq %rax
    ret


