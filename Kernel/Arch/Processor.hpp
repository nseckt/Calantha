/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_PROCESSOR_HPP
#define CALANTHA_PROCESSOR_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/Memory/GDT.hpp>
BEGIN_NAMESPACE(arch);

struct PACKED_ Processor {
  constexpr Processor() = default;
  int64 index = -1;
  mem::gdt::Entries gdt;
  mem::gdt::Pointer ptr;
  mem::gdt::TSS tss;
  static auto boot_processor()  -> Processor*;
  static auto early_init() -> void;
};

END_NAMESPACE(arch);
#endif //CALANTHA_PROCESSOR_HPP
