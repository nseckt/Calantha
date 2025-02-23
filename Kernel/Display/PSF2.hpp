/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_PSF2_HPP
#define CALANTHA_PSF2_HPP
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/Span.hpp>
#include <Kernel/KCore/Result.hpp>
BEGIN_NAMESPACE(psf2);

constexpr uint8 Magic[4]         = {0x72, 0xb5, 0x4a, 0x86};
constexpr uint32 HasUnicodeTable = 0x00000001U;
constexpr uint32 MaxVersion      = 0x00000000U;

struct PACKED_ Header {
  uint8  magic_[4]; /// must be 72 b5 4a 86
  uint32 version_;  /// should always be 0.
  uint32 size_;     /// Size of this header, offset to bitmaps
  uint32 flags_;    /// Flags field.
  uint32 numglyph_; /// number of glyphs
  uint32 bpg_;      /// size (in bytes) of each glyph
  uint32 height_;   /// height in pixels
  uint32 width_;    /// width in pixels
};

class Parser {
public:
  static auto create(const kcore::Span<uint8>&) -> kcore::Result<Parser>;
  NODISCARD_ auto header() const -> const Header*;
private:
  Parser(const Span<uint8>& buff) : buff_(buff) {}
  kcore::Span<uint8> buff_;
};

END_NAMESPACE(psf2);
#endif //CALANTHA_PSF2_HPP
