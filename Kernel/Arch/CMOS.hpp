/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_CMOS_HPP
#define CALANTHA_CMOS_HPP
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(arch::cmos);

NODISCARD_ auto read(uint8 index)   -> uint8;
auto write(uint8 index, uint8 data) -> void;

END_NAMESPACE(arch::cmos);
#endif //CALANTHA_CMOS_HPP
