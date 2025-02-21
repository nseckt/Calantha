/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_CHARCONV_HPP
#define CALANTHA_KCORE_CHARCONV_HPP
#include <Kernel/KCore/StringView.hpp>
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/Result.hpp>
#include <Kernel/KCore/Span.hpp>
BEGIN_NAMESPACE(kcore);

auto from_chars(const StringView& sv, int64& out, int base = 10)  -> Result<void>;
auto from_chars(const StringView& sv, uint64& out, int base = 10) -> Result<void>;

auto to_chars(int64 in, Span<char>& out)  -> Result<usize>;
auto to_chars(uint64 in, Span<char>& out) -> Result<usize>;

constexpr auto tolower(const char ch) -> char {  /// ASCII uppercase + 0x20:
  return ch + static_cast<char>(0x20);           /// produces lowercase.
}

constexpr auto toupper(const char ch) -> char {  /// ASCII lowercase - 0x20:
  return ch - static_cast<char>(0x20);           /// produces uppercase.
}

constexpr auto isspace(const char ch) -> bool {  /// Checks if a character is
  return ch == ' ' || ch == '\t' || ch == '\n';  /// ASCII whitespace.
}

constexpr auto isascii(const char ch) -> bool {  /// Checks if a character is in the ASCII range:
  return ch >= 0;                                /// 0 - 127
}

constexpr auto isdigit(const char ch) -> bool {  /// Checks if a character is
  return ch >= '0' && ch <= '9';                 /// a valid ASCII digit.
}

END_NAMESPACE(kcore);
#endif //CALANTHA_KCORE_CHARCONV_HPP
#ifdef USING_KCORE_GLOBALLY
using kcore::from_chars;
using kcore::to_chars;
using kcore::tolower;
using kcore::toupper;
using kcore::isspace;
using kcore::isascii;
using kcore::isdigit;
#endif
