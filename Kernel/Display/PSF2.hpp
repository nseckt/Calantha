/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_PSF2_HPP
#define CALANTHA_PSF2_HPP
#include <Kernel/KCore/Types.hpp>
BEGIN_NAMESPACE(psf2)

constexpr uint8 Magic = 0x864ab572;
constexpr uint32 HasUnicodeTable = 0x00000001;
constexpr uint32 MaxVersion = 0;

struct PACKED_ Header {
  uint8 magic_[4]; /// must be 72 b5 4a 86
  uint32 version_; /// should always be 0.
  uint32 size_;    /// Size of this header, offset to bitmaps
  uint32 flags;    /// Flags field.
  uint32 numglyph; /// number of glyphs
  uint32 bpg;      /// size (in bytes) of each glyph
  uint32 height;   /// height in pixels
  uint32 width;    /// width in pixels
};

END_NAMESPACE(psf2)
#endif //CALANTHA_PSF2_HPP
