/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_IDT_HPP
#define CALANTHA_IDT_HPP
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(interrupts::idt);

struct PACKED Entry {
  uint16 isr_low;    /// The lower 16 bits of the ISR's address.
  uint16 kernel_cs;  /// The GDT segment selector that the CPU will load into CS before calling the ISR.
  uint8  ist;        /// The IST in the TSS that the CPU will load into RSP.
  uint8  attributes; /// Type and attributes.
  uint16 isr_mid;    /// The higher 16 bits of the lower 32 bits of the ISR's address.
  uint32 isr_high;   /// The higher 32 bits of the ISR's address.
  uint32 reserved;   /// Should be set to zero.
};

struct PACKED Register {
  uint16 limit;      /// Limit.
  uint64 base;       /// Base address of the IDT.
};

END_NAMESPACE(interrupts::idt);
#endif //CALANTHA_IDT_HPP
