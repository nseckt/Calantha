/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/Serial/Outs.hpp>
BEGIN_NAMESPACE(kcore);

template<typename ...Args>
FORCEINLINE_ auto log(Args&&... args) -> void {
#if QEMU_SERIAL_LOGGING_
  serial::outs
    << serial::GreenFG
    << "[ INFO ] "
    << serial::Reset;
  ((serial::outs << args), ...);
#endif
}

template<typename ...Args>
FORCEINLINE_ auto logln(Args&&... args) -> void {
#if QEMU_SERIAL_LOGGING_
  serial::outs
    << serial::GreenFG
    << "[ LOG ] "
    << serial::Reset;
  ((serial::outs << args), ...);
  serial::outs   << '\n';
#endif
}

template<typename ...Args>
FORCEINLINE_ auto err(Args&&... args) -> void {
#if QEMU_SERIAL_LOGGING_
  serial::outs
    << serial::RedFG
    << "[ ERR ] "
    << serial::Reset;
  ((serial::errs << args), ...);
#endif
}

template<typename ...Args>
FORCEINLINE_ auto errln(Args&&... args) -> void {
#if QEMU_SERIAL_LOGGING_
  serial::outs
    << serial::RedFG
    << "[ ERR ] "
    << serial::Reset;
  ((serial::errs << args), ...);
  serial::outs << '\n';
#endif
}

using LogBase = serial::OStream::Base;
FORCEINLINE_ auto setbase(LogBase b) -> void {
#if QEMU_SERIAL_LOGGING_
  serial::outs << b;
#endif
}

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::errln;
using kcore::err;
using kcore::logln;
using kcore::log;
using kcore::setbase;
using kcore::LogBase;
#endif //USING_KCORE_GLOBALLY
