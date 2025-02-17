/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/Boot/VGAText.hpp>
#include <Kernel/Serial/Print.hpp>
BEGIN_NAMESPACE(kcore);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

auto __spin_forever() -> void {
  asm volatile ("cli");
  for(;;) { asm volatile ("hlt"); }
}

auto __fatal_assertion(const char *msg) -> void {
#if VGA_TEXTMODE_
  auto term = VGATerm::create();
  term.clearscr();
  term.chcolour(VGAColour::Red, VGAColour::Black);
  term.putstring(msg);
#elif QEMU_SERIAL_LOGGING_
  SERIAL_PUTS("\n\033[31m");
  SERIAL_PUTS(msg);
  SERIAL_PUTS("\033[0m\nhanging...\n");
#endif
  __spin_forever();
}

#pragma GCC diagnostic pop
END_NAMESPACE(kcore);