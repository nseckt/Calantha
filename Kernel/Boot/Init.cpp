/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/Kcore/Types.hpp>
#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/Vendor/limine.h>
#include <Kernel/KCore/Result.hpp>
#include <Kernel/Serial/SerialIO.hpp>
#include <Kernel/KCore/CharConv.hpp>
#include <Kernel/Arch/CPUID.hpp>
#include <Kernel/KCore/Intrinsics.hpp>
#include <Kernel/KCore/Try.hpp>

namespace {
  __attribute__((used, section(".limine_requests")))
  volatile LIMINE_BASE_REVISION(3);

  __attribute__((used, section(".limine_requests")))
  volatile limine_framebuffer_request fb_req = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0,
    .response = nullptr
  };

  __attribute__((used, section(".limine_requests")))
  volatile limine_kernel_address_request kaddr_req = {
    .id = LIMINE_KERNEL_ADDRESS_REQUEST,
    .revision = 0,
    .response = nullptr
  };

  __attribute__((used, section(".limine_requests_start")))
  volatile LIMINE_REQUESTS_START_MARKER;

  __attribute__((used, section(".limine_requests_end")))
  volatile LIMINE_REQUESTS_END_MARKER;
}

extern "C" {
  int __cxa_atexit(void (*)(void *), void *, void *) { return 0; }
  void __cxa_pure_virtual() { __spin_forever(); }
  void *__dso_handle;
}

extern void (*__init_array[])();
extern void (*__init_array_end[])();
extern "C" uint16 code64_selector;

static auto verify_limine_responses_() -> void {
  ASSERT(LIMINE_BASE_REVISION_SUPPORTED == true);
  ASSERT(kaddr_req.response != nullptr);
  ASSERT(fb_req.response != nullptr);
  ASSERT(fb_req.response->framebuffer_count >= 1);
}

extern "C" void calantha_init() {
  for (usize i = 0; &__init_array[i] != __init_array_end; i++) {
    __init_array[i]();
  }

  serial::com1_init();
  verify_limine_responses_();

  uint16* ptr = (uint16*)0xFFA3FFA3000EB010ULL;
  serial::outs << "This is a test.\n" << ptr << '\n' << 'A';

  /// Framebuffer shennanigans
  limine_framebuffer *framebuffer = fb_req.response->framebuffers[0];
  for (usize i = 0; i < 100; i++) {
    volatile uint32 *fb_ptr = static_cast<volatile uint32 *>(framebuffer->address);
    fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
  }

  /// more dumb shennanigans
  ASSERT(code64_selector == 420, "dis shit aint right");
}
