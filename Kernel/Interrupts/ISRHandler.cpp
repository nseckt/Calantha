/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/Interrupts/ISRHandler.hpp>
#include <Kernel/Interrupts/IDT.hpp>
#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/Serial/Outs.hpp>
#include <Kernel/KCore/Log.hpp>
#include <Kernel/KCore/Span.hpp>

///
/// Singleton handler object.
constinit interrupt::Handler g_isr_handler_{};

///
/// Start - end of stub routine pointers, magic value.
extern "C" uintptr isr_table_start[];
extern "C" uintptr isr_table_end[];
constexpr uintptr TABLE_MAGIC = 0xABFF00ABFF00ABFFULL;

///
/// The default handler routine. Called by ASM ISR stubs.
extern "C" auto calantha_interrupt_handler_(interrupt::Frame*) -> void {
  kcore::__spin_forever();
}

BEGIN_NAMESPACE(interrupt);
constinit const char* g_exception_msgs[32] {
  "division by zero",
  "debug",
  "non-maskable interrupt",
  "breakpoint",
  "detected overflow",
  "out-of-bounds",
  "invalid opcode",
  "no coprocessor",
  "double fault",
  "coprocessor segment overrun",
  "bad TSS",
  "segment not present",
  "stack fault",
  "general protection fault",
  "page fault",
  "unknown interrupt",
  "coprocessor fault",
  "alignment check",
  "machine check",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt",
  "reserved interrupt"
};

auto Handler::get() -> Handler& {
  return g_isr_handler_;
}

auto Handler::init() -> Result<void> {
  const uintptr* beg = isr_table_start;
  const uintptr* end = isr_table_end;

  ASSERT(end > beg);
  ASSERT(end && beg);

  const ptrdiff elem_size = sizeof(uintptr);
  const ptrdiff num_bytes = (end - beg) * elem_size;
  const ptrdiff num_entries = end - beg;

  logln("interrupt::Handler::init():");
  logln("- isr_table_start: ", beg);
  logln("- isr_table_end: ", end);
  logln("- table magic: ", (void*)*end);
  logln("- table size: ", num_bytes, " bytes, ", num_entries, " pointers.");

  ASSERT(num_bytes == 256 * sizeof(uintptr));
  ASSERT(num_entries == 256);
  ASSERT(num_entries == static_cast<ptrdiff>(length_of(idt::g_table)));
  ASSERT(*end == TABLE_MAGIC);

  logln("- Verified ISR pointer table.");
  logln("- Attempting to initialize IDT...");

  return Result<void>::create();
}

END_NAMESPACE(interrupt);

