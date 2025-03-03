/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#define USING_KCORE_GLOBALLY
#include <Kernel/Display/PSF2.hpp>
#include <Kernel/KCore/Memory.hpp>
#include <Kernel/KCore/Try.hpp>
BEGIN_NAMESPACE(psf2);

auto Parser::header() const -> const Header* {
  return ptr_cast<const Header>(buff_.data());
}

auto Parser::create(const Span<uint8>& buff) -> Result<Parser> {
  ERROR_IF(buff.size() < sizeof(Header), ErrC::InvalidArg);

  const auto* header = ptr_cast<const Header>(buff.data());
  ERROR_IF(header->version_ != 0, ErrC::InvalidArg);

  for(usize i = 0; i < length_of(Magic); ++i)
    ERROR_IF(header->magic_[i] != Magic[i], ErrC::InvalidArg);

  return Parser{buff};
}

END_NAMESPACE(psf2);
