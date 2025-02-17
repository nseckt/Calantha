/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_SPAN_HPP
#define CALANTHA_KCORE_SPAN_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/TypeManip.hpp>
#include <Kernel/KCore/Iterator.hpp>
#include <Kernel/KCore/Concepts.hpp>
#include <Kernel/KCore/Assertions.hpp>
BEGIN_NAMESPACE(kcore);

template<Concrete T>
class Span {
public:
  using IteratorType = ContiguousIterator<T>;
  using ValueType    = T;

  ALWAYS_INLINE constexpr auto* data(this auto&& self) {
    return kcore::forward<decltype(self)>(self).elems_;
  }

  ALWAYS_INLINE constexpr auto begin() -> IteratorType {
    return elems_;  /// Provide iterator types...
  }                 ///

  ALWAYS_INLINE constexpr auto end() -> IteratorType {
    return elems_ + size_;
  }

  ALWAYS_INLINE constexpr auto size() const -> usize {
    return size_;   /// Maybe just make size_ public? :/
  }                 ///

  ALWAYS_INLINE constexpr auto empty() const -> bool {
    return size_ == 0;
  }

  ALWAYS_INLINE auto&& front(this auto&& self) {
    ASSERT(!empty(), "Bounds check failure!")
    return kcore::forward<decltype(self)>(self).elems_[ 0 ];
  }

  ALWAYS_INLINE auto&& back(this auto&& self) {
    ASSERT(!empty(), "Bounds check failure!")
    return kcore::forward<decltype(self)>(self).elems_[ self.size_ - 1 ];
  }

  ALWAYS_INLINE auto&& at(this auto&& self, usize i) {
    ASSERT(i < self.size_, "Bounds check failure!");
    return kcore::forward<decltype(self)>(self).elems_[ i ];
  }

  ALWAYS_INLINE constexpr auto&& operator[](this auto&& self, usize i) {
    return kcore::forward<decltype(self)>(self).elems_[ i ];
  }

  ALWAYS_INLINE constexpr Span(T* ptr, usize size)
  : elems_(ptr), size_(size) {}

  template<usize size>
  ALWAYS_INLINE constexpr Span(T (&elems)[size])
  : elems_(elems), size_(size) {}

  constexpr Span(Span&& other)      = default;
  constexpr Span(Span const& other) = default;
  constexpr Span()                  = default;
protected:
  T* elems_   = nullptr;
  usize size_ = 0;
};

END_NAMESPACE(kcore);
#endif //CALANTHA_KCORE_SPAN_HPP
#ifdef USING_KCORE_GLOBALLY
using kcore::Span;
#endif //USING_KCORE_GLOBALLY
