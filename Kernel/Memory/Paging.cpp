/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Memory/Paging.hpp>
#include <Kernel/KCore/Assertions.hpp>
BEGIN_NAMESPACE(mem);

auto get_page_index(IndiceKind indice, void* val) -> usize {
  const uintptr ptr = reinterpret_cast<uintptr>(val);
  switch(indice) {
  case IndiceKind::PML4: return (ptr >> 39) & 0x1FF;
  case IndiceKind::PDPT: return (ptr >> 30) & 0x1FF;
  case IndiceKind::PD:   return (ptr >> 21) & 0x1FF;
  case IndiceKind::PT:   return (ptr >> 12) & 0x1FF;
  case IndiceKind::PHYS: return ptr & 0xFFF;
  default: break;
  }

  UNREACHABLE_ASSERTION();
}

auto get_page_index(IndiceKind indice, uintptr val) -> usize {
  switch(indice) {
  case IndiceKind::PML4: return (val >> 39) & 0x1FF;
  case IndiceKind::PDPT: return (val >> 30) & 0x1FF;
  case IndiceKind::PD:   return (val >> 21) & 0x1FF;
  case IndiceKind::PT:   return (val >> 12) & 0x1FF;
  case IndiceKind::PHYS: return val & 0xFFF;
  default: break;
  }

  UNREACHABLE_ASSERTION();
}

auto get_page_indices(void* addr) -> PageIndices {
  PageIndices indices{};
  indices.pml4_index_ = get_page_index(IndiceKind::PML4, addr);
  indices.pdpt_index_ = get_page_index(IndiceKind::PDPT, addr);
  indices.pd_index_   = get_page_index(IndiceKind::PD, addr);
  indices.pt_index_   = get_page_index(IndiceKind::PT, addr);
  indices.phys_off_   = get_page_index(IndiceKind::PHYS, addr);
  return indices;
}

auto get_page_indices(uintptr addr) -> PageIndices {
  PageIndices indices{};
  indices.pml4_index_ = get_page_index(IndiceKind::PML4, addr);
  indices.pdpt_index_ = get_page_index(IndiceKind::PDPT, addr);
  indices.pd_index_   = get_page_index(IndiceKind::PD, addr);
  indices.pt_index_   = get_page_index(IndiceKind::PT, addr);
  indices.phys_off_   = get_page_index(IndiceKind::PHYS, addr);
  return indices;
}

END_NAMESPACE(mem);
