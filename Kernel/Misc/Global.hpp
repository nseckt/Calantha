/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_GLOBAL_HPP
#define CALANTHA_GLOBAL_HPP

// This file contains macros included into every compilation unit.
// Try to avoid bloating this file so we don't increase compile times.

#define VGA_TEXTMODE_ 1
#define BEGIN_NAMESPACE(NAME) namespace NAME {
#define END_NAMESPACE(NAME) }
#define PAGESIZE 4096
#define ALWAYS_INLINE __attribute__((always_inline))
#define NEVER_INLINE __attribute__((noinline))

#endif //CALANTHA_GLOBAL_HPP
