/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Arch/MSR.hpp>
#include <Kernel/KCore/Limits.hpp>
#include <Kernel/Arch/CPUID.hpp>
BEGIN_NAMESPACE(arch);

NODISCARD_ auto MSR::exists() -> bool {
  CPUID id(1);
  return (id.edx() & (1 << 5)) != 0;
}

NODISCARD_ auto MSR::get() -> uint64 {
  uint32 low, high;
  asm volatile("rdmsr" : "=a"(low), "=d"(high) : "c"(msr_));
  return (static_cast<uint64>(high) << 32) | low;
}

auto MSR::get(uint32& low, uint32& high) -> void {
  uint32 low_, high_;
  asm volatile("rdmsr" : "=a"(low_), "=d"(high_) : "c"(msr_));
  low = low_;
  high = high_;
}

auto MSR::set(uint64 value) -> void {
  uint32 low = value & kcore::NumericLimits<uint32>::max();
  uint32 high = value >> 32;
  asm volatile("wrmsr" ::"a"(low), "d"(high), "c"(msr_));
}

END_NAMESPACE(arch);