/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/Boot/VGAText.hpp>
#include <Kernel/Serial/Outs.hpp>
BEGIN_NAMESPACE(kcore);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

auto __spin_forever() -> void {
  asm volatile ("cli");
  for(;;) { asm volatile ("hlt"); }
}

auto __fatal_assertion(const char *msg) -> void {
#if QEMU_SERIAL_LOGGING_
  serial::com1_puts("\n\n\033[31m");
  serial::com1_puts("\033[1m");
  serial::com1_puts(msg);
  serial::com1_puts("\033[0m\nhanging...\n");
#endif
  __spin_forever();
}

#pragma GCC diagnostic pop
END_NAMESPACE(kcore);