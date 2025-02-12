/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_TYPES_HPP
#define CALANTHA_KCORE_TYPES_HPP
BEGIN_NAMESPACE(kcore);

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

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::uint64;
using kcore::uint32;
using kcore::uint16;
using kcore::uint8;
using kcore::int64;
using kcore::int32;
using kcore::int16;
using kcore::int8;
using kcore::uintptr;
using kcore::intptr;
using kcore::usize;
using kcore::byte;
#endif //USING_KCORE_GLOBALLY
#endif //CALANTHA_TYPES_HPP
