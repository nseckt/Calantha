/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_GLOBAL_HPP
#define CALANTHA_GLOBAL_HPP

#define BEGIN_NAMESPACE(NAME) namespace NAME {
#define END_NAMESPACE(NAME) }

#define BEGIN_ANONYMOUS_NAMESPACE() namespace {
#define END_ANONYMOUS_NAMESPACE() }

// Attribute macros
#define NODISCARD_    [[nodiscard]]
#define UNUSED_       [[maybe_unused]]
#define NORETURN_     [[noreturn]]
#define FALLTHROUGH_  [[fallthrough]]
#define NAKED_        __attribute__((naked))
#define PACKED_       __attribute__((packed))
#define FORCEINLINE_  __attribute__((always_inline)) inline
#define NOINLINE_     __attribute__((noinline))

#endif //CALANTHA_GLOBAL_HPP
