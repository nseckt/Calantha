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
static auto digit_value_(const char ch) -> Option<Int> {
  if (ch >= '0' && ch <= '9') return ch - '0';
  if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
  if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
  return None();
}

static auto is_digit_(char ch, int base) -> bool {
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
static auto from_chars_(const StringView& sv, Int& out) -> Result<void> {
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

  for(; index < sv.size() && is_digit_(sv.at(index), base_); ++index) {
    const Int digit = MUST(digit_value_<Int>(sv.at(index)));
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

static auto append_next_char_(Span<char>& chars, usize& i, char ch) -> Result<void> {
  if(i >= chars.size()) return Error{"buffer too small!", ErrC::Overflow};
  chars.at(i++) = ch;
  return Result<void>::create();
}

template<Integer Int, Int base_>
static auto to_chars_(const Int num, Span<char>& chars) -> Result<usize> {
  if(usize temp_index = 0; num == 0) {
    TRY(append_next_char_(chars, temp_index, '0'));
    return Result<usize>::create(0ULL);
  }

  usize index = 0, curr = num;
  if (NumericLimits<Int>::is_signed && num < 0) {
    curr = -curr;
  }

  while(curr > 0) {
    usize rem  = curr % base_;
    char digit = rem < 10 ? rem + '0' : (rem - 10) + 'A';
    TRY(append_next_char_(chars, index, digit));
    curr /= base_;
  }

  if(NumericLimits<Int>::is_signed && num < 0) {
    TRY(append_next_char_(chars, index, '-'));
  }

  switch(base_) {
  case 16:
    TRY(append_next_char_(chars, index, 'x'));
    TRY(append_next_char_(chars, index, '0'));
    break;
  case 8:
    TRY(append_next_char_(chars, index, '0'));
    break;
  case 2:
    TRY(append_next_char_(chars, index, 'b'));
    TRY(append_next_char_(chars, index, '0'));
    FALLTHROUGH_;
  default: break;
  }

  for(usize start = 0, end = index - 1; start < end; ++start, --end) {
    const char temp = chars.at(start); /// Reverse the characters.
    chars.at(start) = chars.at(end);   ///
    chars.at(end)   = temp;
  }

  return Result<usize>::create(index);
}

auto from_chars(const StringView &sv, int64 &out, int base) -> Result<void> {
  switch (base) {
  case BaseBin: return from_chars_<int64, 2> (sv, out);
  case BaseHex: return from_chars_<int64, 16>(sv, out);
  case BaseDec: return from_chars_<int64, 10>(sv, out);
  case BaseOct: return from_chars_<int64, 8> (sv, out);
  default: break;
  }

  return Error{"Invalid numerical base!", ErrC::InvalidArg};
}

auto from_chars(const StringView &sv, uint64 &out, int base) -> Result<void> {
  switch (base) {
  case BaseBin: return from_chars_<uint64, 2> (sv, out);
  case BaseHex: return from_chars_<uint64, 16>(sv, out);
  case BaseDec: return from_chars_<uint64, 10>(sv, out);
  case BaseOct: return from_chars_<uint64, 8> (sv, out);
  default: break;
  }

  return Error{"Invalid numerical base!", ErrC::InvalidArg};
}

auto to_chars(int64 in, Span<char> &out, int base /* =10 */) -> Result<usize> {
  switch (base) {
  case BaseBin: return to_chars_<int64, 2> (in, out);
  case BaseHex: return to_chars_<int64, 16>(in, out);
  case BaseDec: return to_chars_<int64, 10>(in, out);
  case BaseOct: return to_chars_<int64, 8> (in, out);
  default: break;
  }

  return Error{"Invalid numerical base!", ErrC::InvalidArg};
}

auto to_chars(uint64 in, Span<char> &out, int base /* =10 */) -> Result<usize> {
  switch (base) {
    case BaseBin: return to_chars_<uint64, 2> (in, out);
    case BaseHex: return to_chars_<uint64, 16>(in, out);
    case BaseDec: return to_chars_<uint64, 10>(in, out);
    case BaseOct: return to_chars_<uint64, 8> (in, out);
    default: break;
  }

  return Error{"Invalid numerical base!", ErrC::InvalidArg};
}

END_NAMESPACE(kcore);
