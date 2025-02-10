/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_VGATEXT_HPP
#define CALANTHA_VGATEXT_HPP

#if VGA_TEXTMODE_
#include <Kernel/KCore/Types.hpp>

#define VGATEXT_ADDR   0xB8000U
#define VGATEXT_HEIGHT 25
#define VGATEXT_WIDTH  80

enum class VGA : kcore::uint8 {
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

class VGATerm {
public:
  using Byte  = kcore::uint8;
  using Entry = kcore::uint16;

  static auto create()                      -> VGATerm;
  static auto make_colour(Byte fg, Byte bg) -> Byte;
  static auto make_entry(Byte ch, Byte)     -> Entry;

  auto set_colour(VGA fg, VGA bg) -> VGATerm&;
  auto putchar(kcore::uint8 ch)   -> VGATerm&;
  auto putstring(const char* str) -> VGATerm&;
  auto feedln(kcore::uint32 amnt) -> VGATerm&;
private:
  VGATerm() = default;
  kcore::usize row_;
  kcore::usize col_;
  Entry* buff_;
  Byte colour_;
};

#endif //VGA_TEXTMODE_
#endif //CALANTHA_VGATEXT_HPP
