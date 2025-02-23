/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_ALLOCATORBASE_HPP
#define CALANTHA_ALLOCATORBASE_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/TypeManip.hpp>
#include <Kernel/KCore/Result.hpp>
BEGIN_NAMESPACE(mem);

class AllocatorBase {
public:
  template<typename T>
  using __Result = kcore::Result<T>;

  template<typename T>
  FORCEINLINE_ auto deallocate(this auto&& self, T* ptr) -> __Result<void> {
    return self.template deallocate_<T>(ptr);
  }

  template<typename T, typename ...Args>
  FORCEINLINE_ auto allocate(this auto&& self, Args&&... args) -> T* {
    return self.template allocate_<T>(kcore::forward<Args>(args)...);
  }

  FORCEINLINE_ auto remaining(this auto&& self) -> usize {
    return self.remaining_();
  }

  AllocatorBase() = default;
 ~AllocatorBase() = default;
};

END_NAMESPACE(mem);
#endif //CALANTHA_ALLOCATORBASE_HPP
