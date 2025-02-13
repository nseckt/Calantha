/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_MEMORY_HPP
#define CALANTHA_KCORE_MEMORY_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/TypeTraits.hpp>
#include <Kernel/KCore/TypeManip.hpp>
#include <stddef.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

inline void* operator new(size_t size, void* ptr) noexcept {
  return ptr; /// Placement new.
}

inline void* operator new[](size_t size, void* ptr) noexcept {
  return ptr;
}

#pragma GCC diagnostic pop

BEGIN_NAMESPACE(kcore);
template<typename T>
[[nodiscard]] constexpr auto launder(T* ptr) -> T* {
  return __builtin_launder(ptr);
}

template<typename T, typename ...Args>
constexpr auto construct_at(void* ptr, Args&&... args) -> T* {
  static_assert(!IsArray<T>, "Cannot construct array type");
  return ::new (ptr) T(kcore::forward<Args>(args)...);
}

template<typename T>
constexpr auto destroy_at(T* ptr) -> void {
  static_assert(!IsArray<T>, "Cannot destroy array type");
  ptr->~T(); /// Manually call destructor
}

constexpr inline auto kstrlen(const char *str) -> usize {
  usize len = 0;
  while(str[len]) ++len;
  return len;
}

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::kstrlen;
using kcore::launder;
using kcore::construct_at;
using kcore::destroy_at;
#endif //USING_KCORE_GLOBALLY
#endif //CALANTHA_KCORE_MEMORY_HPP
