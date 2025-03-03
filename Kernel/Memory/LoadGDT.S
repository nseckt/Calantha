/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Memory/SegmentConstants.h>

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
