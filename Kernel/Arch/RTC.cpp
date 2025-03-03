/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <Kernel/Arch/RTC.hpp>
#include <Kernel/Arch/CMOS.hpp>
BEGIN_ANONYMOUS_NAMESPACE();

FORCEINLINE_ auto from_bcd(uint8 val) -> uint8 {
  return (val & 0x0F) + ((val >> 4) * 10);
}

FORCEINLINE_ auto is_updating() -> bool {
  return arch::cmos::read(0x0A) & 0x80;
}

END_ANONYMOUS_NAMESPACE();
BEGIN_NAMESPACE(arch::rtc);

NODISCARD_ auto now() -> Values {
  Values tm{};
  while(!is_updating())    /// FIXME:
    asm volatile("pause"); /// This fucking sucks.

  while(is_updating())
    asm volatile("pause");

  using namespace arch::cmos;
  uint8 statusb = read(0x0B);
  tm.mins = read(0x02);
  tm.hour = read(0x04);
  tm.day  = read(0x07);
  tm.mnth = read(0x08);
  tm.year = read(0x09);
  tm.secs = read(0x00);

  const bool is_pm = tm.hour & 0x80;
  if(!(statusb & 0x04)) {
    tm.mins = from_bcd(tm.mins);
    tm.hour = from_bcd(tm.hour & 0x7F);
    tm.day  = from_bcd(tm.day);
    tm.mnth = from_bcd(tm.mnth);
    tm.year = from_bcd(tm.year);
    tm.secs = from_bcd(tm.secs);
  }

  if (!(statusb & 0x02)) {
    tm.hour %= 12;
    if (is_pm) tm.hour += 12;
  }

  tm.year += 2000;
  return tm;
}

END_NAMESPACE(arch::rtc);