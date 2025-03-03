/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_ARCH_IO_HPP
#define CALANTHA_ARCH_IO_HPP
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(arch);

NODISCARD_ auto in8 (uint16 port) -> uint8;
NODISCARD_ auto in16(uint16 port) -> uint16;
NODISCARD_ auto in32(uint16 port) -> uint32;

auto ignorant_delay(usize microsecs)  -> void;
auto out8 (uint16 port, uint8 value)  -> void;
auto out16(uint16 port, uint16 value) -> void;
auto out32(uint16 port, uint32 value) -> void;

END_NAMESPACE(arch);
#endif //CALANTHA_ARCH_IO_HPP
