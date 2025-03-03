/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/Memory/GDT.hpp>
#include <Kernel/KCore/Log.hpp>
#include <Kernel/Arch/Processor.hpp>
#include <Kernel/Memory/SegmentConstants.h>
BEGIN_NAMESPACE(mem::gdt);

extern "C" void load_gdt_impl_(uintptr gdtr);

auto init(arch::Processor* cpu) -> void {
  if(cpu->index == 0x00)
    logln("- Loading GDT on bootstrap processor.");

  auto& gdt = cpu->gdt;
  cpu->ptr.limit = sizeof(Entries) - 1;
  cpu->ptr.base  = reinterpret_cast<uint64>(&gdt);

  gdt.kcode.access = 0x9A;
  gdt.kcode.granu  = 0x20;
  gdt.kdata.base1  = 0xFE;
  gdt.kdata.access = 0x92;
  gdt.kdata.base2  = 0xCA;
  gdt.udata.access = 0xF2;
  gdt.ucode.access = 0xFA;
  gdt.ucode.granu  = 0x20;
  load_gdt_impl_(reinterpret_cast<uintptr>(&cpu->ptr));
}

auto load(uintptr gdtr) -> void {
  load_gdt_impl_(gdtr); /// ignore this function for now
}

auto Entry::log() -> void {
  setbase(LogBase::Hexadecimal);
  const auto acc_ = access;
  const auto grn_ = granu;

  logln("- access byte: ", acc_);
  logln("- granularity: ", grn_);
  logln("- (base and limit irrelevant)");
  setbase(LogBase::Decimal);
}

auto TSSEntry::log() -> void {
  setbase(LogBase::Hexadecimal);
  const auto b0_ = base0;
  const auto b1_ = base1;  /// Note: this is done to avoid compiler issues
  const auto b2_ = base2;  /// with references to packed fields.
  const auto b3_ = base3;
  const auto ln_ = length;

  logln("- base0: ", b0_);
  logln("- base1: ", b1_);
  logln("- base2: ", b2_);
  logln("- base3: ", b3_);

  setbase(LogBase::Decimal);
  logln("- length: ", ln_);
}

auto Entries::log() -> void {
  logln("Kernel code segment:");
  kcode.log();
  logln("Kernel data segment:");
  kdata.log();
  logln("User code segment:");
  ucode.log();
  logln("User data segment:");
  udata.log();
  logln("Task state segment entry:");
  tss.log();

  setbase(LogBase::Hexadecimal);
  logln("GDT selector offsets:");
  logln("- kernel code segment GDT offset: ", SEG_KCODE);
  logln("- kernel data segment GDT offset: ", SEG_KDATA);
  logln("- user code segment GDT offset: ", SEG_UCODE);
  logln("- user data segment GDT offset: ", SEG_UDATA);
  logln("- TSS GDT entry offset: ", SEG_TSS);
  setbase(LogBase::Decimal);
}

END_NAMESPACE(mem::gdt);