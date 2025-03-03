/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_ARCH_IO_HPP
#define CALANTHA_ARCH_IO_HPP
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(arch);

NODISCARD_ auto in8 (uint16) -> uint8;
NODISCARD_ auto in16(uint16) -> uint16;
NODISCARD_ auto in32(uint16) -> uint32;

auto out8 (uint16, uint8)    -> void;
auto out16(uint16, uint16)   -> void;
auto out32(uint16, uint32)   -> void;

END_NAMESPACE(arch);
#endif //CALANTHA_ARCH_IO_HPP
