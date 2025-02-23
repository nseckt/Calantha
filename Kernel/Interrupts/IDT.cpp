/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Interrupts/IDT.hpp>
BEGIN_NAMESPACE(interrupts::idt);

constinit Entry    g_table[ 256 ]{};
constinit Register g_register{};

END_NAMESPACE(interrupts::idt);