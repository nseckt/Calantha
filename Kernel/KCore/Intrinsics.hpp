/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_INTRINSICS_HPP
#define CALANTHA_KCORE_INTRINSICS_HPP
#include <stddef.h> // stddef.h SHOULD be freestanding...
#include <stdint.h> // This one too. If they aren't freestanding compatible we're fucked.

// IMPORTANT:
// GCC may generate calls to memset, memcpy, memmove,
// and memcmp under certain scenarios, even when compiling
// without linking against libc. Therefore it's crucial we
// provide implementations for these ourselves.

extern "C" {
  void* memcpy(void *dest, const void *src, size_t n);
  void* memset(void *s, int c, size_t n);
  void* memmove(void *dest, const void *src, size_t n);
  int memcmp(const void *s1, const void *s2, size_t n);
}

#endif //CALANTHA_KCORE_INTRINSICS_HPP
