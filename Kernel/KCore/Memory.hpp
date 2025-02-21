/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_MEMORY_HPP
#define CALANTHA_KCORE_MEMORY_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/Concepts.hpp>
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
NODISCARD_ constexpr auto launder(T* ptr) -> T* {
  return __builtin_launder(ptr);
}

template<typename T, typename E>
NODISCARD_ inline auto ptr_cast(E* ptr) -> T* {
  return __builtin_launder(reinterpret_cast<T*>(ptr));
}

template<typename T, typename ...Args>
constexpr auto construct_at(void* ptr, Args&&... args) -> T* {
  static_assert(!IsArray<T>, "Cannot construct array type");
  return ::new (ptr) T(kcore::forward<Args>(args)...);
}

template<typename T>
constexpr auto destroy_at(T* ptr) -> void {
  static_assert(!IsArray<T>, "Cannot destroy array type");
  ptr->~T();         /// Manually call destructor
}

template<typename T, usize sz> requires(sizeof(T) > 0)
constexpr auto length_of([[maybe_unused]] T (&arr)[sz]) -> usize {
  if constexpr (!sz)
    return 0;        /// avoid division by zero in some edge cases
  else               ///
    return sizeof(arr) / sizeof(T);
}

inline auto align(usize align, usize size, void*& ptr, usize& space) -> void* {
  if (space < size)  /// Ensure there's actually enough space.
    return nullptr;  ///

  const uintptr intptr  = reinterpret_cast<uintptr>(ptr);
  const uintptr aligned = (intptr - 1u + align) & -align;
  const uintptr diff    = aligned - intptr;

  if (diff > (space - size))
    return nullptr;  /// ensure we can update by the difference.
                     ///
  space -= diff;
  return ptr = reinterpret_cast<void*>(aligned);
}

template<Character Char>
constexpr auto kstrlen(const Char* str) -> usize {
  usize len = 0;
  while(str[len] != static_cast<Char>(0)) ++len;
  return len;
}

template<Character Char>
constexpr auto kstrcmp(const Char* s1, const Char* s2) -> bool {
  const auto len1 = kcore::kstrlen<Char>(s1);
  const auto len2 = kcore::kstrlen<Char>(s2);

  if(len1 != len2) return false;
  for(usize i = 0; i < len1; i++) if(s1[ i ] != s2[ i ]) return false;
  return true;
}

END_NAMESPACE(kcore);
#endif //CALANTHA_KCORE_MEMORY_HPP
#ifdef USING_KCORE_GLOBALLY
using kcore::kstrlen;
using kcore::launder;
using kcore::construct_at;
using kcore::destroy_at;
#endif //USING_KCORE_GLOBALLY
