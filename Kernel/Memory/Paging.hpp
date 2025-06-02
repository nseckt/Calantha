/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/Kcore/Types.hpp>
BEGIN_NAMESPACE(mem);

constexpr uint64 PagePresent  = 1 << 0;
constexpr uint64 PageWritable = 1 << 1;
constexpr uint64 PageUser     = 1 << 2;
constexpr uint64 PageHuge     = 1 << 7;

struct PageIndices {
  usize pml4_index_;
  usize pdpt_index_;
  usize pd_index_;
  usize pt_index_;
  usize phys_off_;
};

enum class IndiceKind : uint16 {
  PML4  = 0x0001,  /// Page Map Level 4
  PDPT  = 0x0002,  /// Page Directory Pointer Table
  PD    = 0x0003,  /// Page Directory
  PT    = 0x0004,  /// Page Table
  PHYS  = 0x0005,  /// Physical offset into page frame
};

NODISCARD_ auto get_page_index(IndiceKind, void*)   -> usize;
NODISCARD_ auto get_page_index(IndiceKind, uintptr) -> usize;
NODISCARD_ auto get_page_indices(void*)   -> PageIndices;
NODISCARD_ auto get_page_indices(uintptr) -> PageIndices;

END_NAMESPACE(mem);
