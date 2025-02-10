/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/


#include <Kernel/Boot/VGAText.hpp>
#if VGA_TEXTMODE_

auto VGATerm::create() -> VGATerm {
  VGATerm term;
  term.buff_   = (kcore::uint16*)VGATEXT_ADDR;
  term.col_    = 0x00;
  term.row_    = 0x00;
  return term; // TODO FINISH
}

#endif //VGA_TEXTMODE_