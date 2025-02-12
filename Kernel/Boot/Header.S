/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

.set MB2_MAGIC, 0xE85250D6
.set MB2_ARCH,  0x00000000

.section .multiboot
.align 8
header_start:
.long MB2_MAGIC
.long MB2_ARCH
.long header_end - header_start
.long -(MB2_MAGIC + MB2_ARCH + (header_end - header_start))

.word 0
.word 0
.long 8
header_end:
