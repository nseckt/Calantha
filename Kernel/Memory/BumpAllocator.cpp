/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/Memory/BumpAllocator.hpp>
#include <Kernel/KCore/Assertions.hpp>
BEGIN_NAMESPACE(mem);

auto BumpAllocator::operator=(BumpAllocator&& other) -> BumpAllocator& {
  ASSERT(other.is_valid(), "other: null mem region");
  this->beg_ = other.beg_;
  this->cur_ = other.cur_;
  this->end_ = other.end_;
  other.beg_ = nullptr;
  other.cur_ = nullptr; /// Clear out other's pointers
  other.end_ = nullptr; ///
  return *this;
}

BumpAllocator::BumpAllocator(BumpAllocator&& other) {
  ASSERT(other.is_valid(), "null mem region");
  this->beg_ = other.beg_;
  this->cur_ = other.cur_;
  this->end_ = other.end_;
  other.beg_ = nullptr;
  other.cur_ = nullptr; /// Clear out other's pointers
  other.end_ = nullptr; ///
}

BumpAllocator::BumpAllocator(void* begin, void* end) {
  this->beg_ = begin;
  this->cur_ = begin;
  this->end_ = end;
  ASSERT(is_valid());
}

auto BumpAllocator::allocate_block(usize align, usize size) -> void* {
  usize space = difference(cur_, end_);
  if(!size || !is_valid() || !space) return nullptr;

  void* ptr = checked_align_up(
      align,  /// Use T's natural alignment as the boundary
      size,   /// We need to reserve sizeof(T) bytes.
      cur_,   /// Current pointer position.
      space); /// Space remaining from cur_ up to end_.
  return ptr;
}

END_NAMESPACE(mem);