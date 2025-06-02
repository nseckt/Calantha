/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
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

  FORCEINLINE_ constexpr auto* data(this auto&& self) {
    return kcore::forward<decltype(self)>(self).elems_;
  }

  FORCEINLINE_ constexpr auto begin() -> IteratorType {
    return elems_;  /// Provide iterator types...
  }                 ///

  FORCEINLINE_ constexpr auto end() -> IteratorType {
    return elems_ + size_;
  }

  FORCEINLINE_ constexpr auto size() const -> usize {
    return size_;   /// Maybe just make size_ public? :/
  }                 ///

  FORCEINLINE_ constexpr auto empty() const -> bool {
    return size_ == 0;
  }

  FORCEINLINE_ auto&& front(this auto&& self) {
    ASSERT(!empty(), "Bounds check failure!")
    return kcore::forward<decltype(self)>(self).elems_[ 0 ];
  }

  FORCEINLINE_ auto&& back(this auto&& self) {
    ASSERT(!empty(), "Bounds check failure!")
    return kcore::forward<decltype(self)>(self).elems_[ self.size_ - 1 ];
  }

  FORCEINLINE_ auto&& at(this auto&& self, usize i) {
    ASSERT(i < self.size_, "Bounds check failure!");
    return kcore::forward<decltype(self)>(self).elems_[ i ];
  }

  FORCEINLINE_ constexpr auto&& operator[](this auto&& self, usize i) {
    return kcore::forward<decltype(self)>(self).elems_[ i ];
  }

  FORCEINLINE_ constexpr Span(T* ptr, usize size)
  : elems_(ptr), size_(size) {}

  template<usize size>
  FORCEINLINE_ constexpr Span(T (&elems)[size])
  : elems_(elems), size_(size) {}

  constexpr Span(Span&& other)      = default;
  constexpr Span(Span const& other) = default;
  constexpr Span()                  = default;
protected:
  T* elems_   = nullptr;
  usize size_ = 0;
};

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::Span;
#endif //USING_KCORE_GLOBALLY
