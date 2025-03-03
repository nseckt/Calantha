/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Arch/CMOS.hpp>
#include <Kernel/Arch/IO.hpp>
BEGIN_NAMESPACE(arch::cmos);

auto read(const uint8 index) -> uint8 {
  arch::out8(0x70, index);
  return arch::in8(0x71);
}

auto write(uint8 index, uint8 data) -> void {
  arch::out8(0x70, index);
  arch::out8(0x71, data);
}

END_NAMESPACE(arch::cmos);