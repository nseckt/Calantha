/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_CPUID_HPP
#define CALANTHA_CPUID_HPP
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(arch);

class CPUID {
public:
  explicit CPUID(uint32 func, uint32 in_ecx = 0);
  enum FeatureSet : uint32 {
    ECX_SSE3    = 1u << 0u,   /// Streaming SIMD Extensions 3
    ECX_PCLMUL  = 1u << 1u,   /// PCLMULDQ Instruction
    ECX_DTES64  = 1u << 2u,   /// 64-Bit Debug Store
    ECX_MONITOR = 1u << 3u,   /// MONITOR/MWAIT Instructions
    ECX_DS_CPL  = 1u << 4u,   /// CPL Qualified Debug Store
    ECX_VMX     = 1u << 5u,   /// Virtual Machine Extensions
    ECX_SMX     = 1u << 6u,   /// Safer Mode Extensions
    ECX_EST     = 1u << 7u,   /// Enhanced Intel SpeedStep® Technology
    ECX_TM2     = 1u << 8u,   /// Thermal Monitor 2
    ECX_SSSE3   = 1u << 9u,   /// Supplemental Streaming SIMD Extensions 3
    ECX_CID     = 1u << 10u,  /// L1 Context ID
    ECX_SDBG    = 1u << 11u,  /// Silicon Debug (IA32_DEBUG_INTERFACE MSR)
    ECX_FMA     = 1u << 12u,  /// Fused Multiply Add
    ECX_CX16    = 1u << 13u,  /// CMPXCHG16B Instruction
    ECX_XTPR    = 1u << 14u,  /// xTPR Update Control
    ECX_PDCM    = 1u << 15u,  /// Perfmon and Debug Capability (IA32_PERF_CAPABILITIES MSR)
    ECX_PCID    = 1u << 17u,  /// Process Context Identifiers
    ECX_DCA     = 1u << 18u,  /// Direct Cache Access
    ECX_SSE4_1  = 1u << 19u,  /// Streaming SIMD Extensions 4.1
    ECX_SSE4_2  = 1u << 20u,  /// Streaming SIMD Extensions 4.2
    ECX_X2APIC  = 1u << 21u,  /// Extended xAPIC Support
    ECX_MOVBE   = 1u << 22u,  /// MOVBE Instruction
    ECX_POPCNT  = 1u << 23u,  /// POPCNT Instruction
    ECX_TSC     = 1u << 24u,  /// Time Stamp Counter Deadline
    ECX_AES     = 1u << 25u,  /// AES Instruction Extensions
    ECX_XSAVE   = 1u << 26u,  /// XSAVE/XSTOR States
    ECX_OSXSAVE = 1u << 27u,  /// OS-Enabled Extended State Management
    ECX_AVX     = 1u << 28u,  /// Advanced Vector Extensions
    ECX_F16C    = 1u << 29u,  /// 16-bit floating-point conversion instructions
    ECX_RDRAND  = 1u << 30u,  /// RDRAND Instruction
    ECX_HPV     = 1u << 31u,  /// Hypervisor present (always zero on physical CPUs)
    EDX_FPU     = 1u << 0u,   /// Floating-point Unit On-Chip
    EDX_VME     = 1u << 1u,   /// Virtual Mode Extension
    EDX_DE      = 1u << 2u,   /// Debugging Extension
    EDX_PSE     = 1u << 3u,   /// Page Size Extension
    EDX_TSC     = 1u << 4u,   /// Time Stamp Counter
    EDX_MSR     = 1u << 5u,   /// Model Specific Registers
    EDX_PAE     = 1u << 6u,   /// Physical Address Extension
    EDX_MCE     = 1u << 7u,   /// Machine-Check Exception
    EDX_CX8     = 1u << 8u,   /// CMPXCHG8 Instruction
    EDX_APIC    = 1u << 9u,   /// On-chip APIC Hardware
    EDX_SEP     = 1u << 11u,  /// Fast System Call
    EDX_MTRR    = 1u << 12u,  /// Memory Type Range Registers
    EDX_PGE     = 1u << 13u,  /// Page Global Enable
    EDX_MCA     = 1u << 14u,  /// Machine-Check Architecture
    EDX_CMOV    = 1u << 15u,  /// Conditional Move Instruction
    EDX_PAT     = 1u << 16u,  /// Page Attribute Table
    EDX_PSE36   = 1u << 17u,  /// 36-bit Page Size Extension
    EDX_PSN     = 1u << 18u,  /// Processor serial number is present and enabled
    EDX_CLFLUSH = 1u << 19u,  /// CLFLUSH Instruction
    EDX_DS      = 1u << 21u,  ///
    EDX_ACPI    = 1u << 22u,  ///
    EDX_MMX     = 1u << 23u,  ///
    EDX_FXSR    = 1u << 24u,  ///
    EDX_SSE     = 1u << 25u,  /// Streaming SIMD Extensions
    EDX_SSE2    = 1u << 26u,  /// Streaming SIMD Extensions 2
    EDX_SS      = 1u << 27u,  /// Self-Snoop
    EDX_HTT     = 1u << 28u,  /// Multi-Threading
    EDX_TM      = 1u << 29u,  /// Thermal Monitor
    EDX_IA64    = 1u << 30u,  /// IA64 processor emulating x86
    EDX_PBE     = 1u << 31u,  /// Pending Break Enable
  };

  NODISCARD_ uint32 eax() const { return eax_; }
  NODISCARD_ uint32 ebx() const { return ebx_; }
  NODISCARD_ uint32 ecx() const { return ecx_; }
  NODISCARD_ uint32 edx() const { return edx_; }

private:
  uint32 eax_ = 0xFFFFFFFF;   /// Members are modified via CPUID
  uint32 ebx_ = 0xFFFFFFFF;   ///
  uint32 ecx_ = 0xFFFFFFFF;
  uint32 edx_ = 0xFFFFFFFF;
};

inline CPUID::CPUID(uint32 func, uint32 in_ecx) {
  asm volatile("cpuid"
     : "=a"(eax_), "=b"(ebx_), "=c"(ecx_), "=d"(edx_)
     : "a"(func), "c"(in_ecx));
}

END_NAMESPACE(arch);
#endif //CALANTHA_CPUID_HPP
