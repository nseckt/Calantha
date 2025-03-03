/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/Arch/IO.hpp>
#include <Kernel/Serial/COM.hpp>
BEGIN_NAMESPACE(arch);

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

END_NAMESPACE(arch);