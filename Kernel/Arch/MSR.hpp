/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_MSR_HPP
#define CALANTHA_MSR_HPP
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(arch);

class MSR {
public:
  MSR(uint32 msr) : msr_(msr) {}
  MSR() = delete;
  MSR(const MSR&) = default;

  NODISCARD_ static auto exists()     -> bool;
  NODISCARD_ auto get()               -> uint64;
  auto get(uint32& low, uint32& high) -> void;
  auto set(uint64 value)              -> void;
private:
  uint32 msr_{};
};

END_NAMESPACE(arch);
#endif //CALANTHA_MSR_HPP
