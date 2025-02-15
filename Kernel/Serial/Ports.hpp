/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_SERIAL_PORTS_HPP
#define CALANTHA_SERIAL_PORTS_HPP
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(serial);

constexpr uint16 COM1 = 0x3F8;
constexpr uint16 COM2 = 0x2F8;
constexpr uint16 COM3 = 0x3E8;
constexpr uint16 COM4 = 0x2E8;
constexpr uint16 COM5 = 0x5F8;
constexpr uint16 COM6 = 0x4F8;
constexpr uint16 COM7 = 0x5E8;
constexpr uint16 COM8 = 0x4E8;

END_NAMESPACE(serial);
#endif //CALANTHA_SERIAL_PORTS_HPP
