/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/Kcore/Types.hpp>
#include <Kernel/KCore/Assertions.hpp>
#include <Kernel/Vendor/limine.h>
#include <Kernel/KCore/Result.hpp>
#include <Kernel/Serial/Print.hpp>
#include <Kernel/Memory/MMU.hpp>

namespace {
  __attribute__((used, section(".limine_requests")))
  volatile LIMINE_BASE_REVISION(3);

  __attribute__((used, section(".limine_requests")))
  volatile limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0,
    .response = nullptr
  };

  __attribute__((used, section(".limine_requests")))
  volatile limine_kernel_address_request kernel_address_request = {
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

auto get_value(Option<int> i) -> Result<int> { //test lol
  if(i.has_value() && *i > 100) return Result<int>::create(400);
  return Error{"blabla", ErrC::Generic};
}

extern "C" void calantha_init() {
  for (usize i = 0; &__init_array[i] != __init_array_end; i++) {
    __init_array[i]();
  }

  SERIAL_INIT();
  auto entry1 = mem::get_page_index(mem::PageLevel::PML4, 0xFFFFFFFFFFFFFFFF);
  if(entry1 == 511) {
    SERIAL_PUTS("it's the last one!!");
  } else {
    SERIAL_PUTS("No lol!");
  }

  SERIAL_PUTCH('\n');
  ASSERT(LIMINE_BASE_REVISION_SUPPORTED == true);
  ASSERT(kernel_address_request.response != nullptr);
  ASSERT(framebuffer_request.response != nullptr);
  ASSERT(framebuffer_request.response->framebuffer_count >= 1);

  auto val = get_value(300);
  if(val.has_value() && *val == 400) {
    // Fetch the first framebuffer.
    // Note: we assume the framebuffer model is RGB with 32-bit pixels.
    limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    for (usize i = 0; i < 100; i++) {
      volatile uint32 *fb_ptr = static_cast<volatile uint32 *>(framebuffer->address);
      fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
    }
  }

}
