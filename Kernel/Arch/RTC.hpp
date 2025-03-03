/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_RTC_HPP
#define CALANTHA_RTC_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/ClassTraits.hpp>
BEGIN_NAMESPACE(arch::rtc);

struct Values {
  CTA_DEFAULT_CMP(Values);
  constexpr Values() = default;
  uint32 secs = 0;
  uint32 mins = 0;
  uint32 hour = 0;
  uint32 day  = 1;
  uint32 mnth = 1;
  uint32 year = 1970;
};

NODISCARD_ auto now() -> Values;

END_NAMESPACE(arch::rtc);
#endif //CALANTHA_RTC_HPP
