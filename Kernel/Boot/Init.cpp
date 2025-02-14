/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/Kcore/Types.hpp>
#include <Kernel/KCore/Assertions.hpp>
//#include <Kernel/Vendor/limine.h>
#include <Kernel/KCore/Result.hpp>
#include <Kernel/Boot/VGAText.hpp>

extern "C" {
  int __cxa_atexit(void (*)(void *), void *, void *) { return 0; }
  void __cxa_pure_virtual() { __spin_forever(); }
  void *__dso_handle;
}

extern void (*__init_array[])();
extern void (*__init_array_end[])();


// This is just me messing around, ignore this.
auto get_value(Option<int> i) -> Result<int> {
  if(i.has_value() && *i > 100) return Result<int>::create(212);
  return Error{"blabla", ErrC::Generic};
}

extern "C" void calantha_init() {
  for (usize i = 0; &__init_array[i] != __init_array_end; i++) {
    __init_array[i]();
  }

  // This is just me messing around, ignore this.
  auto term = VGATerm::create();
  term.clearscr();

  auto val = get_value(300);
  if(val.has_value() && *val == 400) {
    term.putstring("The value is 400!\n");
  } else {
    term.chcolour(VGAColour::Cyan, VGAColour::Red);
    term.putstring("BLABLABLABLABLABLABLABLABLABLABLA\nBLABLABLABLABLA\nBLABLABLABLABLABLABLABLA\n");
  }

  __spin_forever();
}
