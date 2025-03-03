/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_LOG_HPP
#define CALANTHA_KCORE_LOG_HPP
#include <Kernel/Serial/Outs.hpp>
BEGIN_NAMESPACE(kcore);

template<typename ...Args>
FORCEINLINE_ auto log(Args&&... args) -> void {
#if QEMU_SERIAL_LOGGING_
  ((serial::outs << args), ...);
#endif
}

template<typename ...Args>
FORCEINLINE_ auto logln(Args&&... args) -> void {
#if QEMU_SERIAL_LOGGING_
  ((serial::outs << args), ...);
  serial::outs << '\n';
#endif
}

template<typename ...Args>
FORCEINLINE_ auto err(Args&&... args) -> void {
#if QEMU_SERIAL_LOGGING_
  ((serial::errs << args), ...);
#endif
}

template<typename ...Args>
FORCEINLINE_ auto errln(Args&&... args) -> void {
#if QEMU_SERIAL_LOGGING_
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
#endif //CALANTHA_KCORE_LOG_HPP
#ifdef USING_KCORE_GLOBALLY
using kcore::errln;
using kcore::err;
using kcore::logln;
using kcore::log;
using kcore::setbase;
using kcore::LogBase;
#endif //USING_KCORE_GLOBALLY
