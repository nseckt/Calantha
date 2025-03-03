/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Arch/Processor.hpp>
BEGIN_NAMESPACE(arch);
static constinit Processor bp_;

auto Processor::early_init() -> void {
  bp_.index = 0x00; // Boot processor ID
}

auto Processor::boot_processor() -> Processor* {
  return &bp_;
}

END_NAMESPACE(arch);