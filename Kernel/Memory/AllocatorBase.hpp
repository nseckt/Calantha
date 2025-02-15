/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_ALLOCATORBASE_HPP
#define CALANTHA_ALLOCATORBASE_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/Concepts.hpp>
#include <Kernel/KCore/TypeManip.hpp>
BEGIN_NAMESPACE(mem);

class AllocatorBase {
public:
  template<typename T,  typename ...Args>
  auto allocate(this auto&& self, Args&&... args) -> T* {
    static_assert(!kcore::IsReference<T>);
    return self.__allocate(kcore::forward<Args>(args)...);
  }

  template<typename T>
  auto deallocate(this auto&& self, T* ptr) -> void {
    return self.__deallocate(ptr);
  }

  template<typename T>
  static constexpr auto is_allocator() -> bool {
    return kcore::IsBaseOf<AllocatorBase, kcore::Decay<T>>;
  }

 ~AllocatorBase() = default;
  AllocatorBase() = default;
};

BEGIN_NAMESPACE(mem);
#endif //CALANTHA_ALLOCATORBASE_HPP
