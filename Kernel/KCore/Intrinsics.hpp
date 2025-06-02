/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once

/// stddef.h and stdint.h are assumed to be
/// freestanding compatible.
#include <stddef.h>
#include <stdint.h>

/// IMPORTANT:
/// GCC may generate calls to memset, memcpy, memmove,
/// and memcmp under certain scenarios, even when compiling
/// without linking against libc. Therefore it's crucial we
/// provide implementations for these ourselves.

extern "C" {
  void* memcpy(void *dest, const void *src, size_t n);
  void* memset(void *s, int c, size_t n);
  void* memmove(void *dest, const void *src, size_t n);
  int memcmp(const void *s1, const void *s2, size_t n);
}
