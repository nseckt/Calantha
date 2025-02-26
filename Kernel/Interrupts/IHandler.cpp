/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Interrupts/IHandler.hpp>
#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/Serial/SerialIO.hpp>

extern "C" auto interrupt_handler_(interrupt::Frame*) -> void {
  kcore::__spin_forever();
}

