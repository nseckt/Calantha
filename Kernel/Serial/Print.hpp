/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_SERIAL_PRINT_HPP
#define CALANTHA_SERIAL_PRINT_HPP
#include <Kernel/KCore/Memory.hpp>
#include <Kernel/KCore/Types.hpp>
#include <Kernel/Serial/Ports.hpp>
#include <Kernel/Serial/IO.hpp>
BEGIN_NAMESPACE(serial);

#if QEMU_SERIAL_LOGGING_
#define SERIAL_PUTS(STR) ::serial::__com1_puts(STR)
#define SERIAL_PUTCH(CH) ::serial::__com1_putch(CH)
#define SERIAL_INIT()    ::serial::__com1_init()

inline auto __com1_init() -> void {
  serial::out8(COM1 + 1, 0x00);
  serial::out8(COM1 + 3, 0x80);
  serial::out8(COM1 + 0, 0x02);
  serial::out8(COM1 + 1, 0x00);
  serial::out8(COM1 + 3, 0x03);
  serial::out8(COM1 + 2, 0xC7);
  serial::out8(COM1 + 4, 0x0B);
}

inline auto __com1_putch(const char ch) -> void {
  while ((serial::in8(COM1 + 5) & 0x20) == 0)
    asm volatile("nop");

  serial::out8(COM1, ch);
}

inline auto __com1_puts(const char* str) -> void {
  for(usize i = 0; i < kcore::kstrlen(str); i++)
    __com1_putch(str[i]);
}

#else
#define SERIAL_PUTS(STR)
#define SERIAL_PUTCH(CH)
#define SERIAL_INIT()
#endif //QEMU_SERIAL_LOGGING_

END_NAMESPACE(serial);
#endif //CALANTHA_SERIAL_PRINT_HPP
