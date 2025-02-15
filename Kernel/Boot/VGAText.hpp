/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_VGATEXT_HPP
#define CALANTHA_VGATEXT_HPP

#if VGA_TEXTMODE_
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/ClassTraits.hpp>

#define VGATEXT_ADDR   0xB8000U
#define VGATEXT_HEIGHT 25
#define VGATEXT_WIDTH  80

using VGAByte  = uint8;
using VGAEntry = uint16;

struct VGAColour final {
CTA_MAKE_COMPARABLE_MEMBER(VGAColour, val_);
  enum Value_ : VGAByte {
    Black      = 0x00,
    Blue       = 0x01,
    Green      = 0x02,
    Cyan       = 0x03,
    Red        = 0x04,
    Magenta    = 0x05,
    Brown      = 0x06,
    LightGrey  = 0x07,
    DarkGrey   = 0x08,
    LightBlue  = 0x09,
    LightGreen = 0x0A,
    LightCyan  = 0x0B,
    LightRed   = 0x0C,
  };

  static auto create(VGAByte fg, VGAByte bg) -> VGAColour;
  auto as_entry(VGAByte ch) const -> VGAEntry;

  VGAByte val_ = LightGrey | (Black << 4);
  constexpr VGAColour(const Value_ v) : val_(v) {}
  constexpr VGAColour() = default;
};

class VGATerm {
public:
  static auto create()            -> VGATerm;
  auto putstring(const char* str) -> VGATerm&;
  auto putchar(VGAByte ch)        -> VGATerm&;
  auto feedln()                   -> VGATerm&;
  auto clearscr()                 -> VGATerm&;
  auto chcolour(VGAByte, VGAByte) -> VGATerm&;
private:
  VGATerm() = default;
  usize row_{};
  usize col_{};
  VGAEntry* buff_{};
  VGAColour colour_{};
};

#endif //VGA_TEXTMODE_
#endif //CALANTHA_VGATEXT_HPP
