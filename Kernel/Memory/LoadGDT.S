/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

.set SEG_NULL,  0x00
.set SEG_KCODE, 0x08
.set SEG_KDATA, 0x10
.set SEG_UCODE, 0x18
.set SEG_UDATA, 0x20
.set SEG_TSS,   0x28

.code64
.section .text

.global load_gdt_impl_
.type load_gdt_impl_, @function
load_gdt_impl_:
    lgdt (%rdi)
    sub $16, %rsp
    movq $SEG_KCODE, 8(%rsp)
    movabsq $gdt_longret_dest, %rax
    mov %rax, (%rsp)
    lretq

gdt_longret_dest:
    mov $SEG_KDATA, %ax
    mov %ax, %ss
    mov $0,  %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    ret
