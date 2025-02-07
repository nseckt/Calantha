/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#.section .bss
#.align 16
#stack_bottom:
#.skip 16384
#stack_top:

.code32
.section .text
.global _start
.type _start @function
_start:
    movl $0x2f4b2f4f, (0xb8000)
    cli
spin:
    hlt
    jmp spin
