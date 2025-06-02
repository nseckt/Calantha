/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(mem);

constexpr uint64 KiB = 1024;
constexpr uint64 MiB = 1024 * KiB;
constexpr uint64 GiB = 1024 * MiB;
constexpr uint64 TiB = 1024 * GiB;
constexpr uint64 PiB = 1024 * TiB;
constexpr uint64 EiB = 1024 * PiB;

constexpr uint64 KB = 1000;
constexpr uint64 MB = 1000 * KB;
constexpr uint64 GB = 1000 * MB;
constexpr uint64 TB = 1000 * GB;
constexpr uint64 PB = 1000 * TB;
constexpr uint64 EB = 1000 * PB;

END_NAMESPACE(mem);