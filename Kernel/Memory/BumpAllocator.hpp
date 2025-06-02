/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/Memory/AllocatorBase.hpp>
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/Memory.hpp>
#include <Kernel/KCore/Concepts.hpp>
#include <Kernel/KCore/TypeManip.hpp>
#include <Kernel/KCore/ClassTraits.hpp>
#include <Kernel/KCore/Result.hpp>
BEGIN_NAMESPACE(mem);

class BumpAllocator : public AllocatorBase {
CTA_MAKE_NONCOPYABLE(BumpAllocator);
public:
  template<typename T>
  FORCEINLINE_ auto deallocate_(UNUSED_ T* ptr) -> kcore::Result<T> {
    return kcore::Error{kcore::ErrC::NImplemented};
  }

  template<kcore::TrivialDTOR T, typename ...Args>
  NODISCARD_ FORCEINLINE_ auto allocate_(Args&&... args) -> T* {
    using namespace kcore;
    void* ptr = allocate_block(alignof(T), sizeof(T));
    if(ptr == nullptr) return nullptr;
    return construct_at<T>(ptr, forward<Args>(args)...);
  }

  NODISCARD_ FORCEINLINE_ auto is_valid() const -> bool {
    return beg_ && cur_ && end_;
  }

  NODISCARD_ FORCEINLINE_ auto is_within_range(void* ptr) const -> bool {
    return ptr >= beg_ && ptr <= end_;
  }

  auto allocate_block(usize align, usize size) -> void*;
  auto operator=(BumpAllocator&& other) -> BumpAllocator&;
  explicit operator bool() const { return is_valid(); }

 ~BumpAllocator() = default;
  BumpAllocator(BumpAllocator&& other);
  BumpAllocator(void* begin, void* end);
private:
  void* beg_ = nullptr;
  void* cur_ = nullptr;
  void* end_ = nullptr;
};

END_NAMESPACE(mem);