/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_LIMITS_HPP
#define CALANTHA_KCORE_LIMITS_HPP
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(kcore);

template<typename T>
struct NumericLimits {
  static_assert("T is not an integral type!");
};

template<>
struct NumericLimits<int64> {
  constexpr static int64 max() { return __INT64_MAX__; }
  constexpr static int64 min() { return -__INT64_MAX__ - 1; }
  constexpr static bool is_signed = true;
};

template<>
struct NumericLimits<uint64> {
  constexpr static uint64 max() { return __UINT64_MAX__; }
  constexpr static uint64 min() { return 0ULL; }
  constexpr static bool is_signed = false;
};

template<>
struct NumericLimits<int32> {
  constexpr static uint64 max() { return __INT32_MAX__; }
  constexpr static uint64 min() { return -__INT32_MAX__ - 1; }
  constexpr static bool is_signed = true;
};

template<>
struct NumericLimits<uint32> {
  constexpr static uint64 max() { return __UINT32_MAX__; }
  constexpr static uint64 min() { return 0; }
  constexpr static bool is_signed = false;
};

template<>
struct NumericLimits<int16> {
  constexpr static uint64 max() { return __INT16_MAX__; }
  constexpr static uint64 min() { return -__INT16_MAX__ - 1; }
  constexpr static bool is_signed = true;
};

template<>
struct NumericLimits<uint16> {
  constexpr static uint64 max() { return __UINT16_MAX__; }
  constexpr static uint64 min() { return 0; }
  constexpr static bool is_signed = false;
};

template<>
struct NumericLimits<int8> {
  constexpr static uint64 max() { return __INT8_MAX__; }
  constexpr static uint64 min() { return -__INT8_MAX__ - 1; }
  constexpr static bool is_signed = true;
};

template<>
struct NumericLimits<uint8> {
  constexpr static uint64 max() { return __UINT8_MAX__; }
  constexpr static uint64 min() { return 0; }
  constexpr static bool is_signed = false;
};

template<>
struct NumericLimits<char8_t> {
  constexpr static uint64 max() { return __UINT8_MAX__; }
  constexpr static uint64 min() { return 0; }
  constexpr static bool is_signed = false;
};

template<>
struct NumericLimits<bool> {
  constexpr static uint64 max() { return true; }
  constexpr static uint64 min() { return false; }
  constexpr static bool is_signed = false;
};

END_NAMESPACE(kcore);
#endif //CALANTHA_KCORE_LIMITS_HPP
#ifdef USING_KCORE_GLOBALLY
using kcore::NumericLimits;
#endif //USING_KCORE_GLOBALLY