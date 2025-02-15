/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_TYPES_HPP
#define CALANTHA_KCORE_TYPES_HPP

// Note: do not place these
// inside of the kcore namespace.

using uint64  = __UINT64_TYPE__;
using uint32  = __UINT32_TYPE__;
using uint16  = __UINT16_TYPE__;
using uint8   = __UINT8_TYPE__;
using int64   = __INT64_TYPE__;
using int32   = __INT32_TYPE__;
using int16   = __INT16_TYPE__;
using int8    = __INT8_TYPE__;
using uintptr = __UINTPTR_TYPE__;
using intptr  = __INTPTR_TYPE__;
using usize   = __SIZE_TYPE__;
using byte    = uint8;

static_assert(sizeof(uintptr) == sizeof(void*));
static_assert(sizeof(uintptr) == sizeof(uint64));
static_assert(sizeof(byte) == 1);

#endif //CALANTHA_TYPES_HPP
