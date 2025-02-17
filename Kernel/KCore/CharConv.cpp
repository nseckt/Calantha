/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/KCore/CharConv.hpp>
#include <Kernel/KCore/Try.hpp>
#include <Kernel/KCore/Option.hpp>
#include <Kernel/KCore/Limits.hpp>
BEGIN_NAMESPACE(kcore);

constexpr int BaseHex = 16;
constexpr int BaseDec = 10;
constexpr int BaseOct = 8;
constexpr int BaseBin = 2;

template<Integer Int>
static auto __digit_value(const char ch) -> Option<Int> {
  if (ch >= '0' && ch <= '9') return ch - '0';
  if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
  if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
  return None();
}

static auto __is_digit(char ch, int base) -> bool {
  if(ch >= 'A' && ch <= 'Z') ch = tolower(ch);
  switch (base) {
  case BaseBin: return ch == '1' || ch == '0';
  case BaseHex: return (ch >= 'a' && ch <= 'f') || (ch >= '0' && ch <= '9');
  case BaseDec: return ch >= '0' && ch <= '9';
  case BaseOct: return ch >= '0' && ch <= '7';
  default: break;
  }

  return false;
}

template<Integer Int, Int base_>
static auto __from_chars(const StringView& sv, Int& out) -> Result<void> {
  out = 0; bool neg = false;
  if(sv.empty()) return Error{ErrC::InvalidArg};
  if(sv == "0")  return Result<void>::create();

  usize index;
  for(index = 0; index < sv.size() && isspace(sv[index]); ++index);
  if(index >= sv.size()) return Error{ErrC::InvalidArg};

  if(const char ch = sv.at(index); ch == '+' || ch == '-') {
    neg = ch == '-'; /// Two's complement negation still required,
    ++index;         /// even for unsigned types.
  }

  for(; index < sv.size() && __is_digit(sv.at(index), base_); ++index) {
    const Int digit = MUST(__digit_value<Int>(sv.at(index)));
    const Int maxi  = NumericLimits<Int>::max();
    if(out > (maxi - digit) / base_) return Error{ErrC::Overflow};
    out = out * base_ + digit;
  }

  if(neg == true) {
    const bool sign = NumericLimits<Int>::is_signed;
    const Int mini  = NumericLimits<Int>::min();
    if (out == mini && sign) return Error{ErrC::Overflow};
    out = -out;
  }

  return Result<void>::create();
}

auto from_chars(const StringView &sv, int64 &out, int base) -> Result<void> {
  switch (base) {
  case BaseBin: return __from_chars<int64, 2> (sv, out);
  case BaseHex: return __from_chars<int64, 16>(sv, out);
  case BaseDec: return __from_chars<int64, 10>(sv, out);
  case BaseOct: return __from_chars<int64, 8> (sv, out);
  default: break;
  }

  return Error{"Invalid numerical base!", ErrC::InvalidArg};
}

auto from_chars(const StringView &sv, uint64 &out, int base) -> Result<void> {
  switch (base) {
    case BaseBin: return __from_chars<uint64, 2> (sv, out);
    case BaseHex: return __from_chars<uint64, 16>(sv, out);
    case BaseDec: return __from_chars<uint64, 10>(sv, out);
    case BaseOct: return __from_chars<uint64, 8> (sv, out);
    default: break;
  }

  return Error{"Invalid numerical base!", ErrC::InvalidArg};
}

END_NAMESPACE(kcore);
