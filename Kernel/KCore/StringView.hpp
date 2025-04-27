/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_STRINGVIEW_HPP
#define CALANTHA_KCORE_STRINGVIEW_HPP
#include <Kernel/KCore/Memory.hpp>
#include <Kernel/KCore/Iterator.hpp>
#include <Kernel/KCore/Assertions.hpp>
BEGIN_NAMESPACE(kcore);

template<Character Char>
class StringView_ {
public:
  using IteratorType = ContiguousIterator<AddConst<Char>>;
  using CharType     = AddConst<Char>;

  FORCEINLINE_ constexpr auto data() const -> CharType* {
    return elems_;
  }

  FORCEINLINE_ constexpr auto size() const -> usize {
    return size_;   /// Stinky dinky private data member
  }                 ///

  FORCEINLINE_ constexpr auto empty() const -> bool {
    return size_ == 0;
  }

  FORCEINLINE_ constexpr auto begin() -> IteratorType {
    return elems_;  /// Provide iterator types...
  }                 ///

  FORCEINLINE_ constexpr auto end() -> IteratorType {
    return elems_ + size_;
  }

  constexpr auto operator==(const StringView_& other) const -> bool {
    if(other.size_ != this->size_) return false;
    for(usize i = 0; i < size_; ++i) if(other[i] != (*this)[i]) return false;
    return true;
  }

  constexpr auto operator!=(const StringView_& other) const -> bool {
    if(other.size_ != this->size_) return false;
    for(usize i = 0; i < size_; ++i) if(other[i] != (*this)[i]) return true;
    return false;
  }

  constexpr auto operator[](usize i) const -> const Char& {
    return elems_[ i ];
  }

  FORCEINLINE_ auto at(usize i) const -> const Char& {
    ASSERT(i < size_, "Bounds check failure!");
    return elems_[ i ];
  }

  FORCEINLINE_ constexpr StringView_(CharType* ptr)
  : elems_(ptr), size_(kstrlen(ptr)) {}

  FORCEINLINE_ constexpr StringView_(CharType* ptr, usize len)
  : elems_(ptr), size_(len) {}

  constexpr StringView_(StringView_&&)      = default;
  constexpr StringView_(StringView_ const&) = default;
  constexpr StringView_()                   = default;
protected:
  CharType* elems_ = nullptr;
  usize size_ = 0;
};

using StringView    = StringView_<char>;
using U16StringView = StringView_<char16_t>;
using U8StringView  = StringView_<char8_t>;
END_NAMESPACE(kcore);

inline auto operator ""_sv(const char* ptr, usize len) -> kcore::StringView {
  return kcore::StringView{ ptr, len };
}

inline auto operator ""_sv(const char8_t* ptr, usize len) -> kcore::U8StringView {
  return kcore::U8StringView{ ptr, len };
}

inline auto operator ""_sv(const char16_t* ptr, usize len) -> kcore::U16StringView {
  return kcore::U16StringView{ ptr, len };
}

#endif //CALANTHA_KCORE_STRINGVIEW_HPP
#ifdef USING_KCORE_GLOBALLY
using kcore::StringView;
using kcore::U16StringView;
using kcore::U8StringView;
#endif //USING_KCORE_GLOBALLY
