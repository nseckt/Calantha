/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

.code64

.extern kmain
.type kmain, @function

.extern kinit
.type kinit, @function

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
.skip 32768
stack_top:


.section .text
.global _start
.type _start, @function
_start:
    cli  /* Clear interrupt flag */
    cld  /* Clear direction flag */

    movq $stack_top, %rsp
    call clear_page_tables

    andq $0xFFFFFFFFFFFFFFF0, %rsp
    call kinit

    andq $0xFFFFFFFFFFFFFFF0, %rsp
    call kmain

halt:
    cli
1:
    hlt
    jmp 1b

clear_page_tables:
    movq $init_pml4, %rdi
    call clear_table

    movq $init_pdpt, %rdi
    call clear_table

    movq $init_pd, %rdi
    call clear_table

    movq $init_pt, %rdi
    call clear_table
    ret

clear_table:
    movq $512, %rcx
    xorq %rax, %rax
    rep stosq
    ret
