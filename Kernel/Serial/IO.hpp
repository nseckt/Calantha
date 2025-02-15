#ifndef CALANTHA_SERIAL_IO_HPP
#define CALANTHA_SERIAL_IO_HPP
#include <Kernel/Serial/Ports.hpp>
BEGIN_NAMESPACE(serial);

inline auto in8(uint16 port) -> uint8 {
  uint8 value;
  asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
  return value;
}

inline auto in16(uint16 port) -> uint16 {
  uint16 value;
  asm volatile("inw %1, %0" : "=a"(value) : "Nd"(port));
  return value;
}

inline auto in32(uint16 port) -> uint32 {
  uint32 value;
  asm volatile("inl %1, %0" : "=a"(value) : "Nd"(port));
  return value;
}

inline auto out8(uint16 port, uint8 value) -> void {
  asm volatile("outb %0, %1" :: "a"(value), "Nd"(port));
}

inline auto out16(uint16 port, uint16 value) -> void {
  asm volatile("outw %0, %1" :: "a"(value), "Nd"(port));
}

inline auto out32(uint16 port, uint32 value) -> void {
  asm volatile("outl %0, %1" :: "a"(value), "Nd"(port));
}

END_NAMESPACE(serial);
#endif //CALANTHA_SERIAL_IO_HPP
