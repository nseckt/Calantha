/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_GLOBAL_HPP
#define CALANTHA_GLOBAL_HPP

#define QEMU_SERIAL_LOGGING_ 1
#define VGA_TEXTMODE_ 0
#define ASSERTIONS_ENABLED_ 1

#define BEGIN_NAMESPACE(NAME) namespace NAME {
#define END_NAMESPACE(NAME) }

// Attribute macros
#define NODISCARD_    [[nodiscard]]
#define PACKED_       __attribute__((packed))
#define FORCEINLINE_  __attribute__((always_inline))
#define NOINLINE_     __attribute__((noinline))

#endif //CALANTHA_GLOBAL_HPP
