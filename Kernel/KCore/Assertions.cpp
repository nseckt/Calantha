/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/Boot/VGAText.hpp>
BEGIN_NAMESPACE(kcore);

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
#endif
  __spin_forever();
}

END_NAMESPACE(kcore);