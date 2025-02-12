/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#if VGA_TEXTMODE_
#include <Kernel/Init/VGAText.hpp>
#include <Kernel/KCore/Memory.hpp>

auto VGATerm::create() -> VGATerm {
  VGATerm term;
  term.buff_   = reinterpret_cast<kcore::uint16*>(VGATEXT_ADDR);
  term.col_    = 0x00;
  term.row_    = 0x00;
  term.colour_ = VGAColour::create(VGAColour::LightGrey, VGAColour::Black);
  return term;
}

auto VGAColour::as_entry(VGAByte ch) const -> VGAEntry {
  const auto left  = static_cast<kcore::uint16>(ch);
  const auto right = static_cast<kcore::uint16>(val_);
  return left | (right << 8);
}

auto VGAColour::create(VGAByte fg, VGAByte bg) -> VGAColour {
  VGAColour colour;
  colour.val_ = fg | (bg << 4);
  return colour;
}

auto VGATerm::clearscr() -> VGATerm& {
  const VGAEntry entry = VGAColour::create(
    VGAColour::LightGrey,
    VGAColour::Black).as_entry(' ');

  for(kcore::usize y = 0; y < VGATEXT_HEIGHT; y++) {
    for(kcore::usize x = 0; x < VGATEXT_WIDTH; x++) {
      const kcore::usize index = y * VGATEXT_WIDTH + x;
      buff_[index] = entry;
    }
  }

  col_ = 0;        /// Reset row and column values.
  row_ = 0;        ///
  return *this;
}

auto VGATerm::chcolour(VGAByte fg, VGAByte bg) -> VGATerm& {
  colour_ = VGAColour::create(fg, bg);
  return *this;
}

auto VGATerm::feedln() -> VGATerm& {
  col_ = 0;
  if(++row_ >= VGATEXT_HEIGHT) row_ = 0;
  return *this;
}

auto VGATerm::putchar(VGAByte ch) -> VGATerm& {
  if(ch == '\n') { /// If it's a line feed character:
    feedln();      /// move down 1 row and return.
    return *this;
  }

  const kcore::usize index = row_ * VGATEXT_WIDTH + col_;
  buff_[index] = colour_.as_entry(ch);

  if(++col_ >= VGATEXT_WIDTH) {
    col_ = 0;
    if(++row_ >= VGATEXT_HEIGHT) {
      row_ = 0;
    }              /// Update row and column values,
  }                /// ensure we don't "overflow" the terminal buffer.

  return *this;
}

auto VGATerm::putstring(const char *str) -> VGATerm& {
  for(kcore::usize i = 0; i < kcore::kstrlen(str); i++)
    putchar(str[i]);

  return *this;
}

#endif //VGA_TEXTMODE_
