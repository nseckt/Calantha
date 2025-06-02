/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/KCore/Types.hpp>
#include <Kernel/Memory/SegmentConstants.h>

namespace arch { struct Processor; }
BEGIN_NAMESPACE(mem::gdt);

auto init(arch::Processor* cpu) -> void;
auto load(uintptr gdtr)         -> void;

struct PACKED_ Entry {
  constexpr Entry() = default;
  uint16 limit  = 0x00;
  uint16 base0  = 0x00;
  uint8  base1  = 0x00;
  uint8  access = 0x00;
  uint8  granu  = 0x00;
  uint8  base2  = 0x00;
  auto log() -> void;
};

struct PACKED_ Pointer {
  constexpr Pointer() = default;
  uint16 limit = 0x00;
  uint64 base  = 0x00;
};

struct PACKED_ TSSEntry {
  constexpr TSSEntry() = default;
  uint16 length = 0x00;
  uint16 base0  = 0x00;
  uint8  base1  = 0x00;
  uint8  flags1 = 0x00;
  uint8  flags2 = 0x00;
  uint8  base2  = 0x00;
  uint32 base3  = 0x00;
  uint32 reserved = 0x00;
  auto log() -> void;
};

struct PACKED_ TSS {
  constexpr TSS() = default;
  uint32 reserved0 = 0x00;
  uint64 rsp[3]{};
  uint64 reserved1 = 0x00;
  uint64 ist[7]{};
  uint64 reserved2 = 0x00;
  uint16 reserved3 = 0x00;
  uint16 iomapbase = 0x00;
};

struct PACKED_ Entries {
  constexpr Entries() = default;
  Entry null;
  Entry kcode;
  Entry kdata;
  Entry ucode;
  Entry udata;
  TSSEntry tss;
  auto log() -> void;
};

#if __has_builtin(__builtin_offsetof)
  static_assert(__builtin_offsetof(Entries, kcode) == SEG_KCODE);
  static_assert(__builtin_offsetof(Entries, kdata) == SEG_KDATA);
  static_assert(__builtin_offsetof(Entries, ucode) == SEG_UCODE);
  static_assert(__builtin_offsetof(Entries, udata) == SEG_UDATA);
  static_assert(__builtin_offsetof(Entries, tss)   == SEG_TSS);
#else
# warning "Cannot verify GDT offsets..."
#endif

static_assert(sizeof(TSSEntry) == 16);
static_assert(sizeof(Entry)    == 8);
static_assert(sizeof(Pointer)  == 10);

END_NAMESPACE(mem::gdt);