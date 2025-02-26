/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

.code64
.section .text

.extern calantha_interrupt_handler_
.type calantha_interrupt_handler_, @function

isr_dispatch_stub:
    cld

    ## Set up the interrupt frame
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %rbp
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    movq %rsp, %rdi
    call calantha_interrupt_handler_

    ## Restore registers.
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rbp
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax

    addq $16, %rsp
    iretq


.macro make_isr num
    isr_\num:
.if !(\num == 8 || \num == 17 || \num == 21 || \num == 29 || \num == 30 || (\num >= 10 && \num <= 14))
    pushq $0
.endif
    pushq $\num
    jmp isr_dispatch_stub
.endm

.altmacro
.macro make_isr_ptr num
    .quad isr_\num
.endm

.section .text
.set i, 0
.rept 256
    make_isr %i
    .set i, i + 1
.endr

.section .data
.global isr_table_start
isr_table_start:

.set j, 0
.rept 256
    make_isr_ptr %j
    .set j, j + 1
.endr

.global isr_table_end
isr_table_end:
