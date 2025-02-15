/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

.code64

.extern calantha_init
.type calantha_init, @function

/* Page table structures. */
.section .page_tables, "aw", @nobits
.align 4096
.global init_pml4
init_pml4:
.skip 4096
.global init_pdpt
init_pdpt:
.skip 4096
.global init_pd
init_pd:
.skip 4096
.global init_pt
init_pt:
.skip 4096

.section .stack, "aw", @nobits
stack_bottom:
.skip 16384
stack_top:

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
    movq $stack_top, %rsp

    call clear_pagetables

    movq $gdt_ptr, %rax
    lgdt (%rax)

    sub $16, %rsp
    movq $CODE64_SELECTOR_OFFSET, 8(%rsp)
    movabsq $longret_dest, %rax
    mov %rax, (%rsp)
    lretq

clear_pagetables:
    movq $init_pml4, %rdi
    movq $512, %rcx
    xorq %rax, %rax
    rep stosq

    movq $init_pdpt, %rdi
    movq $512, %rcx
    xorq %rax, %rax
    rep stosq

    movq $init_pd, %rdi
    movq $512, %rcx
    xorq %rax, %rax
    rep stosq

    movq $init_pt, %rdi
    movq $512, %rcx
    xorq %rax, %rax
    rep stosq

    ret

longret_dest:
    mov $0, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    andq $0xFFFFFFFFFFFFFFF0, %rsp
    call calantha_init

halt:
    cli
1:
    hlt
    jmp 1b
