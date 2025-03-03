/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Serial/Outs.hpp>
BEGIN_NAMESPACE(serial);

constinit OStream outs;
constinit OStream errs;

auto com1_init() -> void {
  arch::out8(COM1 + 1, 0x00);
  arch::out8(COM1 + 3, 0x80);
  arch::out8(COM1 + 0, 0x02);
  arch::out8(COM1 + 1, 0x00);
  arch::out8(COM1 + 3, 0x03);
  arch::out8(COM1 + 2, 0xC7);
  arch::out8(COM1 + 4, 0x0B);
}

auto com1_putch(const char ch) -> void {
  while ((arch::in8(COM1 + 5) & 0x20) == 0) {
    asm volatile("nop");
  }

  arch::out8(COM1, ch);
}

auto com1_puts(const char* str) -> void {
  for(usize i = 0; i < kcore::kstrlen(str); i++)
    com1_putch(str[i]);
}

auto early_init() -> void {
  com1_init();
}

END_NAMESPACE(serial);
