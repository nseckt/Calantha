/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_OPTION_HPP
#define CALANTHA_KCORE_OPTION_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/TypeManip.hpp>
#include <Kernel/KCore/Concepts.hpp>
#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/Kcore/Memory.hpp>
BEGIN_NAMESPACE(kcore);

struct None_ {
  unsigned char dummy_value_ = 0;
  constexpr None_() = default;
};

inline constexpr auto None() -> None_ {
  return None_{};
}

template <Concrete T>
class Option {
public:
  using ValueType     = T;
  using ReferenceType = T&;
  using PointerType   = T*;

  [[nodiscard]] ALWAYS_INLINE auto value() & -> ReferenceType {
    ASSERT(has_value_, "Option has no contained type!");
    return *kcore::launder<T>(reinterpret_cast<T*>(&value_));
  }

  [[nodiscard]] ALWAYS_INLINE auto value() const& -> const T& {
    ASSERT(has_value_, "Option has no contained type!");
    return *kcore::launder<const T>(reinterpret_cast<const T*>(&value_));
  }

  [[nodiscard]] ALWAYS_INLINE auto value() && -> ValueType {
    ASSERT(has_value_, "Option has no contained type!");
    return release_value(); /// rvalues should release the contained type.
  }                         ///

  ALWAYS_INLINE auto release_value() -> ValueType {
    ASSERT(has_value_, "Option has no contained type!");
    T released = kcore::move( value() );
    value().~T();           /// We'll have to manually call the destructor.
    has_value_ = false;     ///
    return released;
  }

  ALWAYS_INLINE auto clear() -> void {
    if(has_value_)
      value().~T();
    has_value_ = false;
  }

  ALWAYS_INLINE auto value_or(T&& other) const -> ValueType {
    if(has_value_) return value();
    return other;
  }

  ALWAYS_INLINE auto operator=(Option&& other) noexcept -> Option& {
    if(&other == this) return *this;
    clear();
    if(other.has_value_) {
      has_value_ = true;
      kcore::construct_at<T>(&value_, other.release_value());
    }

    return *this;
  }

  ALWAYS_INLINE auto operator=(const Option& other) -> Option& {
    if(&other == this) return *this;
    clear();
    if(other.has_value_) {
      has_value_ = true;
      kcore::construct_at<T>(&value_, other.value());
    }

    return *this;
  }

  template<typename ...Args>
  ALWAYS_INLINE auto emplace(Args&&... args) -> void {
    clear();
    has_value_ = true;
    kcore::construct_at<T>(&value_, kcore::forward<Args>(args)...);
  }

  template<typename ...Args>
  ALWAYS_INLINE static auto create(Args&&... args) -> Option {
    return Option{ kcore::forward<Args>(args)... };
  }

  template<typename ...Args> requires ConstructibleFrom<T, Args...>
  ALWAYS_INLINE Option(Args&&... args) {
    kcore::construct_at<T>(&value_, kcore::forward<Args>(args)...);
    has_value_ = true;
  }

  ALWAYS_INLINE Option(const Option& other) {
    if(!other.has_value_) return;
    kcore::construct_at<T>( &value_, other.value() );
    has_value_ = true;
  }

  ALWAYS_INLINE Option(Option&& other) {
    if(!other.has_value_) return;
    kcore::construct_at<T>( &value_, other.release_value() );
    has_value_ = true;
  }

  auto operator->() const -> const T* { return &value(); }
  auto operator->() -> T*             { return &value(); }
  auto operator*() const -> const T&  { return value();  }
  auto operator*() -> T&              { return value();  }

  auto has_value() const -> bool { return has_value_; }
  explicit operator bool() const { return has_value_; }

  Option() = default;
  Option(None_&&) {}
 ~Option() { clear(); }
private:
  bool has_value_{false};
  alignas(T) uint8 value_[ sizeof(T) ]{};
};

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::Option;
using kcore::None;
using kcore::None_;
#endif //USING_KCORE_GLOBALLY
#endif //CALANTHA_KCORE_OPTION_HPP
