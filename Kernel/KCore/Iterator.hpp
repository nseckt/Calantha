/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/KCore/TypeManip.hpp>
BEGIN_NAMESPACE(kcore);

template<typename T>
class ContiguousIterator {
public:
  using PointerType   = T*;
  using ReferenceType = T&;
  using ValueType     = T;

  constexpr auto operator*(this auto&& self) -> auto&& {
    return *kcore::forward<decltype(self)>(self).ptr_;
  }

  constexpr auto operator->(this auto&& self) -> auto* {
    return kcore::forward<decltype(self)>(self).ptr_;
  }

  constexpr auto operator++() -> ContiguousIterator& {
    ++ptr_;        /// Simply increment the internal pointer
    return *this;  /// and return self.
  }

  constexpr auto operator++(int) -> ContiguousIterator {
    ContiguousIterator temp = *this;
    ++(*this);     /// Modify self, return the previous
    return temp;   /// incremented value.
  }

  constexpr auto operator--() -> ContiguousIterator& {
    --ptr_;        /// Simply decrement the internal pointer
    return *this;  /// and return self.
  }

  constexpr auto operator--(int) -> ContiguousIterator {
    ContiguousIterator temp = *this;
    --(*this);     /// Modify self, return the previous
    return temp;   /// incremented value.
  }

  constexpr auto operator==(const ContiguousIterator& other) -> bool {
    return other.ptr_ == this->ptr_;
  }

  constexpr auto operator!=(const ContiguousIterator& other) -> bool {
    return other.ptr_ != this->ptr_;
  }

  constexpr ContiguousIterator(PointerType ptr) : ptr_(ptr) {}
  constexpr ContiguousIterator(ContiguousIterator&&) = default;
  constexpr ContiguousIterator(const ContiguousIterator&) = default;
  constexpr ContiguousIterator() = default;
protected:
  PointerType ptr_{};
};

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::ContiguousIterator;
#endif //USING_KCORE_GLOBALLY
