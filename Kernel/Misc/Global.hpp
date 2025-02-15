/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_GLOBAL_HPP
#define CALANTHA_GLOBAL_HPP

#define virtual // Disallow virtual methods on classes
#define QEMU_SERIAL_LOGGING_ 1
#define VGA_TEXTMODE_ 1

#define BEGIN_NAMESPACE(NAME) namespace NAME {
#define END_NAMESPACE(NAME) }
#define PAGESIZE 4096

// GCC attribute macros
#define PACKED         __attribute__((packed))
#define ALWAYS_INLINE  __attribute__((always_inline))
#define NEVER_INLINE   __attribute__((noinline))

#endif //CALANTHA_GLOBAL_HPP
