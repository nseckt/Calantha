/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/Kcore/Types.hpp>
#include <Kernel/Boot/VGAText.hpp>
//#include <Kernel/KCore/Assertions.hpp>
//#include <Kernel/KCore/Result.hpp>

extern "C" uint8 kernel_physical_start_[];
extern "C" uint8 kernel_physical_end_[];

extern "C" uint64 boot_pml4[512];
extern "C" uint64 boot_pdpt[512];
extern "C" uint64 boot_pd[512];

// auto get_option(const int x) -> Option<int> {
//   if(x > 10) return 420;
//   return None();
// }
//

extern "C" void init() {
  auto term = VGATerm::create();
  term.clearscr();
  term.putstring("Hello, 64 bit world!\n");

  // auto res = get_option(22);
}
