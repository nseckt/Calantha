/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/KCore/ClassTraits.hpp>
#include <Kernel/KCore/Types.hpp>
#include <Kernel/Kcore/Concepts.hpp>
#include <Kernel/KCore/Option.hpp>
BEGIN_NAMESPACE(kcore);

struct ErrC {
CTA_MAKE_COMPARABLE_MEMBER(ErrC, value_);
  enum Value_ : uint16 {
    None,         /// No error has occurred.
    NotFound,     /// The resource could not be found.
    InvalidArg,   /// A provided argument is incorrect or malformed.
    NoMemory,     /// There's no memory left! For something....
    NImplemented, /// This function/method/feature is not yet implemented.
    Overflow,     /// This would cause an overflow somewhere.
    Generic,      /// For when you can't think of anything.
  };

  Value_ value_ = None;
  constexpr ErrC(Value_ v) : value_(v) {}
  constexpr ErrC() = default;
};

struct Error {
  using MessageType_ = const char*;
  using CodeType_    = ErrC;

  MessageType_ msg_ = "---";
  CodeType_ code_{};

  constexpr Error(CodeType_ code) : code_(code) {}
  constexpr Error(MessageType_ msg, CodeType_ code) : msg_(msg), code_(code) {}
  constexpr Error()  = default;
  constexpr ~Error() = default;
};

template<Concrete T, Concrete E = Error>
class Result_ {
public:
  using ValueType = T;
  using ErrorType = E;

  template<typename ...Args>
  NODISCARD_ static auto create(Args&&... args) -> Result_ {
    return T{kcore::forward<Args>(args)...};
  }

  FORCEINLINE_ auto value_or(T&& other) const -> ValueType {
    if(value_) return value_.value();
    return other;
  }

  FORCEINLINE_ auto&& value(this auto&& self) {
    return kcore::forward<decltype(self)>(self).value_.value();
  }

  FORCEINLINE_ auto&& error(this auto&& self) {
    return kcore::forward<decltype(self)>(self).error_.value();
  }

  FORCEINLINE_ auto release_value(this auto&& self) -> ValueType {
    return kcore::forward<decltype(self)>(self).value_.release_value();
  }

  FORCEINLINE_ auto release_error(this auto&& self) -> ErrorType {
    return kcore::forward<decltype(self)>(self).error_.release_value();
  }

  auto operator->(this auto&& self) -> decltype(&self.value_.value()) {
    using __PointerType = decltype(&self.value_.value());
    static_assert(IsPointer<__PointerType>, "&value_.value() does not produce a pointer!");
    return &self.value_.value();
  }

  auto operator*(this auto&& self) -> decltype(self.value_.value()) {
    using __ReferenceType = decltype(self.value_.value());
    static_assert(IsReference<__ReferenceType>, "value_.value() does not produce a reference!");
    return self.value_.value();
  }

  auto has_value() const -> bool { return value_.has_value(); }
  explicit operator bool() const { return value_.has_value(); }

  Result_(const ValueType& val) : value_(val) {}
  Result_(ValueType&& val)      : value_(kcore::move(val)) {}
  Result_(const ErrorType& err) : error_(err) {}
  Result_(ErrorType&& err)      : error_(kcore::move(err)) {}

  Result_(Result_&& other)      = default;
  Result_(Result_ const& other) = default;
 ~Result_() = default;
private:
  Option<T> value_;
  Option<E> error_;
};

struct VoidResult_ {
  unsigned char dummy_value_ = 0;
  constexpr VoidResult_() = default;
};

template<typename T>
struct ResultDispatch_ {
  using Type = Result_<T>;
};

template<>
struct ResultDispatch_<void> {
  using Type = Result_<VoidResult_>;
};

template<typename T>
using Result = typename ResultDispatch_<T>::Type;

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::Result;
using kcore::ErrC;
using kcore::Error;
#endif //USING_KCORE_GLOBALLY
