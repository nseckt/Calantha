/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_SERIAL_IO_HPP
#define CALANTHA_SERIAL_IO_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/Serial/COM.hpp>
#include <Kernel/Arch/IO.hpp>
#include <Kernel/KCore/CharConv.hpp>
#include <Kernel/KCore/StringView.hpp>
#include <Kernel/KCore/Concepts.hpp>
#include <Kernel/KCore/TypeManip.hpp>
BEGIN_NAMESPACE(serial);

auto early_init()            -> void;
auto com1_init()             -> void;
auto com1_puts(const char*)  -> void;
auto com1_putch(char)        -> void;

class OStream {
public:
  using Chars_  = kcore::StringView;
  using Port_   = uint16;

  enum class Base : int {
    Decimal     = 10,
    Binary      = 2,
    Hexadecimal = 16,
    Octal       = 8,
  };

  template<kcore::Signed Int>
  FORCEINLINE_ auto operator<<(const Int num) -> OStream& {
    const int64 max_t = static_cast<int64>(num);
    char buff[40]{};

    kcore::Span<char> span(buff);
    if(kcore::to_chars(max_t, span, base_).has_value()) {
      buff[39] = '\0'; /// Ensure null termination
      put_chars(buff); /// Send buffer
    }

    return *this;
  }

  template<kcore::Unsigned Int>
  FORCEINLINE_ auto operator<<(const Int num) -> OStream& {
    const uint64 max_t = static_cast<uint64>(num);
    char buff[40]{};

    kcore::Span<char> span(buff);
    if(kcore::to_chars(max_t, span, base_).has_value()) {
      buff[39] = '\0'; /// Ensure null termination
      put_chars(buff); /// Send buffer
    }

    return *this;
  }

  template<kcore::Pointer Ptr> requires kcore::IsVoidPtr<Ptr>
  FORCEINLINE_ auto operator<<(const Ptr ptr) -> OStream& {
    const uint64 max_t = reinterpret_cast<uint64>(ptr);
    char buff[40]{};

    kcore::Span<char> span(buff);
    if(kcore::to_chars(max_t, span, 16).has_value()) {
      buff[39] = '\0';  /// Ensure null termination
      put_chars(buff);  /// Send buffer
    }

    return *this;
  }

  FORCEINLINE_ auto put_chars(const Chars_& sv) -> OStream& {
    for(usize i = 0; i < sv.size(); ++i) arch::out8(port_, sv.at(i));
    return *this;
  }

  FORCEINLINE_ auto operator<<(const Base base) -> OStream& {
    base_ = static_cast<kcore::UnderlyingType<Base>>(base);
    return *this;
  }

  FORCEINLINE_ auto operator<<(const Chars_& sv) -> OStream& {
    return put_chars(sv);
  }

  FORCEINLINE_ auto operator<<(char ch) -> OStream& {
    arch::out8(port_, ch);
    return *this;
  }

  ~OStream() = default;
  constexpr OStream(Port_ port) : port_(port) {}
  constexpr OStream() = default;
private:
  int base_   = 10;
  Port_ port_ = COM1;
};

///
/// Global serial output stream objects
extern constinit OStream outs;
extern constinit OStream errs;

///
/// Colour constants for ASCII compliant terminals
constexpr char Reset[]     = "\033[0m";
constexpr char Bold[]      = "\033[1m";
constexpr char Underline[] = "\033[4m";
constexpr char GreenFG[]   = "\033[32m";
constexpr char YellowFG[]  = "\033[33m";
constexpr char BlueFG[]    = "\033[34m";
constexpr char MagentaFG[] = "\033[35m";
constexpr char CyanFG[]    = "\033[36m";
constexpr char WhiteFG[]   = "\033[37m";
constexpr char RedFG[]     = "\033[91m";

END_NAMESPACE(serial);
#endif //CALANTHA_SERIAL_IO_HPP
