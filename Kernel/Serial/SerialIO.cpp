/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Serial/SerialIO.hpp>
BEGIN_NAMESPACE(serial);

constinit OStream outs;
constinit OStream errs;

auto in8(uint16 port) -> uint8 {
  uint8 value;
  asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
  return value;
}

auto in16(uint16 port) -> uint16 {
  uint16 value;
  asm volatile("inw %1, %0" : "=a"(value) : "Nd"(port));
  return value;
}

auto in32(uint16 port) -> uint32 {
  uint32 value;
  asm volatile("inl %1, %0" : "=a"(value) : "Nd"(port));
  return value;
}

auto out8(uint16 port, uint8 value) -> void {
  asm volatile("outb %0, %1" :: "a"(value), "Nd"(port));
}

auto out16(uint16 port, uint16 value) -> void {
  asm volatile("outw %0, %1" :: "a"(value), "Nd"(port));
}

auto out32(uint16 port, uint32 value) -> void {
  asm volatile("outl %0, %1" :: "a"(value), "Nd"(port));
}

auto com1_init() -> void {
  out8(COM1 + 1, 0x00);
  out8(COM1 + 3, 0x80);
  out8(COM1 + 0, 0x02);
  out8(COM1 + 1, 0x00);
  out8(COM1 + 3, 0x03);
  out8(COM1 + 2, 0xC7);
  out8(COM1 + 4, 0x0B);
}

auto com1_putch(const char ch) -> void {
  while ((in8(COM1 + 5) & 0x20) == 0) {
    asm volatile("nop");
  }

  out8(COM1, ch);
}

auto com1_puts(const char* str) -> void {
  for(usize i = 0; i < kcore::kstrlen(str); i++)
    com1_putch(str[i]);
}

END_NAMESPACE(serial);

