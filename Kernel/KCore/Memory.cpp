/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/KCore/Memory.hpp>
#include <Kernel/KCore/Assertions.hpp>
BEGIN_NAMESPACE(kcore);

NODISCARD_ auto align_up(const usize align, void* ptr) -> void* {
  const uintptr intptr  = reinterpret_cast<uintptr>(ptr);
  const uintptr mask    = align - 1u;
  const uintptr aligned = (intptr + mask) & ~mask;
  return reinterpret_cast<void*>(aligned);
}

NODISCARD_ auto align_down(usize align, void *ptr) -> void* {
  const uintptr intptr  = reinterpret_cast<uintptr>(ptr);
  const uintptr mask    = align - 1u;
  const uintptr aligned = intptr & ~mask;
  return reinterpret_cast<void*>(aligned);
}

NODISCARD_ auto checked_align_up(usize align, usize size, void*& ptr, usize& space) -> void* {
  if (space < size || (align & (align - 1)) != 0)
    return nullptr;       /// Check size, alignment must be a power of 2.

  const uintptr intptr  = reinterpret_cast<uintptr>(ptr);
  const uintptr aligned = (intptr + (align - 1u)) & ~(align - 1u);
  const uintptr diff    = aligned - intptr;
  const uintptr after   = intptr + diff + size;

  if (diff + size > space) /// ensure we can update by the difference.
    return nullptr;        ///

  ptr = reinterpret_cast<void*>(after);
  space -= diff + size;
  return reinterpret_cast<void*>(aligned);
}

NODISCARD_ auto difference(void* start, void* end) -> usize {
  ASSERT(end >= start, "Invalid memory region");
  const uintptr start_ = reinterpret_cast<uintptr>(start);
  const uintptr end_   = reinterpret_cast<uintptr>(end);
  return end_ - start_;
}

END_NAMESPACE(kcore);
