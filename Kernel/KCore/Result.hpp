/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_RESULT_HPP
#define CALANTHA_KCORE_RESULT_HPP
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
    Generic,      /// For when you can't think of anything.
  };

  Value_ value_ = None;
  constexpr ErrC(Value_ v) : value_(v) {}
  constexpr ErrC() = default;
};

struct Error {
  using MessageType_ = const char*;
  using CodeType_    = ErrC;

  MessageType_ msg_ = nullptr;
  CodeType_ code_{};

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
  [[nodiscard]] static auto create(Args&&... args) -> Result_ {
    return Result_{ kcore::forward<Args>(args)... };
  }

  ALWAYS_INLINE auto value_or(T&& other) const -> ValueType {
    if(value_) return value_.value();
    return other;
  }

  [[nodiscard]] ALWAYS_INLINE auto value() -> T& {
    return value_.value();
  }

  [[nodiscard]] ALWAYS_INLINE auto error() -> E& {
    return error_.value();
  }

  auto operator->() const -> const T* { return &value_.value(); }
  auto operator->() -> T*             { return &value_.value(); }
  auto operator*() const -> const T&  { return value_.value();  }
  auto operator*() -> T&              { return value_.value();  }

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

template<typename T>
struct ResultDispatch_ {
  using Type = Result_<T>;
};

template<>
struct ResultDispatch_<void> {
  using Type = Result_<None_>;
};

template<typename T>
using Result = typename ResultDispatch_<T>::Type;

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::Result;
using kcore::ErrC;
using kcore::Error;
#endif //USING_KCORE_GLOBALLY
#endif //CALANTHA_KCORE_RESULT_HPP
