/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Arch/Shutdown.hpp>
#include <Kernel/Arch/IO.hpp>
BEGIN_NAMESPACE(arch);

auto qemu_shutdown() -> void {
  out16(0x604, 0x2000); /// This will close qemu.
  out16(0xb004, 0x2000);
}

END_NAMESPACE(arch);
