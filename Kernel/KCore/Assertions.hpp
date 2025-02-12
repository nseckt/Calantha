/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_ASSERTIONS_HPP
#define CALANTHA_KCORE_ASSERTIONS_HPP
#include <Kernel/Misc/MacroUtils.hpp>
BEGIN_NAMESPACE(kcore);

#define FATAL(MSG) ::kcore::__fatal_assertion("FATAL :: " MSG);
#define PANIC(MSG) ::kcore::__fatal_assertion("PANIC :: " MSG " -- " SOURCE_LOC)
#define UNREACHABLE_ASSERTION() PANIC("Default assertion - unreachable branch.")
#define ASSERT(COND, ...) if( !(COND)) { PANIC("Assertion \"" #COND "\" failed! " __VA_ARGS__); }

[[noreturn]] auto __fatal_assertion(const char* msg) -> void;
[[noreturn]] auto __spin_forever() -> void;

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::__fatal_assertion;
using kcore::__spin_forever;
#endif //USING_KCORE_GLOBALLY
#endif //CALANTHA_KCORE_ASSERTIONS_HPP
