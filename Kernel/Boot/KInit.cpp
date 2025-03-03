/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/Log.hpp>
#include <Kernel/Arch/Processor.hpp>
#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/Memory/GDT.hpp>

extern "C" {
  int __cxa_atexit(void (*)(void *), void *, void *) { return 0; }
  void __cxa_pure_virtual() { __spin_forever(); }
  void *__dso_handle;
}

extern void (*__init_array[])();
extern void (*__init_array_end[])();

extern "C" void kinit() {
  for (usize i = 0; &__init_array[i] != __init_array_end; i++) {
    __init_array[i]();
  }

  using namespace arch;
  using namespace mem;

  Processor::early_init();
  auto* cpu = Processor::boot_processor();

#if QEMU_SERIAL_LOGGING_
  serial::early_init();
  logln("calantha_init() entry:");
  logln("- initialized serial/COM1");
  logln("- constructed cxx objects");
#endif

  gdt::init(cpu);
  logln("- loaded GDT on bootstrap processor:");
  cpu->gdt.log();

  logln(serial::RedFG);
  cpu->gdt.kdata.access = 0x92;
  if(cpu->gdt.kdata.access == 0x92) {
    logln("ITS 0X92");
  } else {
    logln("ITS NOT 0x92!");
  }
  logln(serial::Reset);
}