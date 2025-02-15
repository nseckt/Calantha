/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_MMU_HPP
#define CALANTHA_MMU_HPP
#include <Kernel/Kcore/Types.hpp>
#include <Kernel/KCore/Concepts.hpp>
#include <Kernel/KCore/TypeManip.hpp>
BEGIN_NAMESPACE(mem);

constexpr uint64 PagePresent  = 1 << 0;
constexpr uint64 PageWritable = 1 << 1;
constexpr uint64 PageUser     = 1 << 2;
constexpr uint64 PageHuge     = 1 << 7;

enum class PageLevel : uint64 {
  PML4  = 39, /// Page Map Level 4.
  PDPT  = 30, /// Page Directory Pointer Table
  PD    = 21, /// Page Directory
  PT    = 12, /// Page Table
};

template<typename T> requires kcore::IsPointer<T>
constexpr auto get_page_index(PageLevel p, T val) -> usize {
  const uint64 shift = kcore::to_underlying(p);
  return (reinterpret_cast<uintptr>(val) >> shift) & 0x1FF;
}

constexpr auto get_page_index(PageLevel p, uintptr val) -> usize {
  const uint64 shift = kcore::to_underlying(p);
  return (val >> shift) & 0x1FF;
}

END_NAMESPACE(mem);
#endif //CALANTHA_MMU_HPP
