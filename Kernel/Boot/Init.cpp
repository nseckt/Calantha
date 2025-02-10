/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

//#include <Kernel/Boot/VGAText.hpp>

// .section .page_tables, "aw", @nobits
// .align 4096
//
// .global boot_pml4
// boot_pml4:
// .skip 4096
//
// .global boot_pdpt
// boot_pdpt:
// .skip 4096
//
// .global boot_pd
// boot_pd:
// .skip 4096

#define USING_KCORE_GLOBALLY
#include "Kernel/KCore/Types.hpp"

extern "C" uint8 kernel_physical_start_[];
extern "C" uint8 kernel_physical_end_[];

extern "C" void init() {


}
