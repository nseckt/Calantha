/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_ARRAY_HPP
#define CALANTHA_KCORE_ARRAY_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/TypeManip.hpp>
#include <Kernel/KCore/Concepts.hpp>
#include <Kernel/KCore/Iterator.hpp>
#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/KCore/Span.hpp>
BEGIN_NAMESPACE(kcore);

template<DefaultConstructible T, usize sz_>
class Array {
public:
  using ValueType    = T;
  using IteratorType = ContiguousIterator<T>;

  FORCEINLINE_ constexpr auto* data(this auto&& self) {
    return kcore::forward<decltype(self)>(self).elems_;
  }

  FORCEINLINE_ constexpr auto size() const -> usize {
    return sz_;     /// Chat is this pointless
  }                 ///

  FORCEINLINE_ constexpr auto empty() const -> bool {
    return sz_ == 0;
  }

  FORCEINLINE_ constexpr auto begin() -> IteratorType {
    return buff_;   /// Provide contiguous iterator types
  }                 ///

  FORCEINLINE_ constexpr auto end() -> IteratorType {
    return buff_ + sz_;
  }

  FORCEINLINE_ constexpr auto span() -> Span<T> {
    return Span<T>{buff_};
  }

  FORCEINLINE_ constexpr auto fill(const ValueType& v) -> void {
    for(usize i = 0; i < sz_; i++) buff_[i] = v;
  }

  FORCEINLINE_ auto&& front(this auto&& self) {
    ASSERT(!empty(), "Bounds check failure!")
    return kcore::forward<decltype(self)>(self).buff_[ 0 ];
  }

  FORCEINLINE_ auto&& back(this auto&& self) {
    ASSERT(!empty(), "Bounds check failure!")
    return kcore::forward<decltype(self)>(self).buff_[ sz_ - 1 ];
  }

  FORCEINLINE_ auto&& at(this auto&& self, usize i) {
    ASSERT(i < self.size_, "Bounds check failure!");
    return kcore::forward<decltype(self)>(self).buff_[ i ];
  }

  FORCEINLINE_ constexpr auto&& operator[](this auto&& self, usize i) {
    return kcore::forward<decltype(self)>(self).buff_[ i ];
  }

  FORCEINLINE_ constexpr Array(T (&arr)[sz_]) {
    for(usize i = 0; i < sz_; i++) buff_[ i ] = arr[ i ];
  }

  FORCEINLINE_ constexpr Array(T (&&arr)[sz_]) {
    for(usize i = 0; i < sz_; i++) buff_[ i ] = kcore::move(arr[ i ]);
  }

  template<AreAll<T> ...Args>
  FORCEINLINE_ constexpr Array(Args&&... args) : buff_(kcore::forward<Args>(args)...)  {}

  constexpr Array() = default;
  constexpr Array(const Array&) = default;
  constexpr Array(Array&&) = default;
private:
  T buff_[ sz_ ]{};
};

END_NAMESPACE(kcore);
#endif //CALANTHA_KCORE_ARRAY_HPP
#ifdef USING_KCORE_GLOBALLY
using kcore::Array;
#endif
