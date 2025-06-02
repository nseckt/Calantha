/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once

#define CTA_MAKE_COMPARABLE_IMPL_(OP, MB, CLASS)               \
  bool operator OP (const CLASS& other) const {                \
    return other OP this->MB;                                  \
  }                                                            \

#define CTA_MAKE_COMPARABLE_MEMBER_IMPL_(SELF, MB, OP)         \
  bool operator OP (const SELF& other) const {                 \
    return other.MB OP this->MB;                               \
  }                                                            \

#define CTA_MAKE_COMPARABLE_ON(CLASS, MB)                      \
  public:                                                      \
    CTA_MAKE_COMPARABLE_IMPL_(==, MB, CLASS)                   \
    CTA_MAKE_COMPARABLE_IMPL_(!=, MB, CLASS)                   \

#define CTA_MAKE_COMPARABLE_MEMBER(SELF, MB)                   \
  public:                                                      \
    CTA_MAKE_COMPARABLE_MEMBER_IMPL_(SELF, MB, ==)             \
    CTA_MAKE_COMPARABLE_MEMBER_IMPL_(SELF, MB, !=)             \

#define CTA_MAKE_NONCOPYABLE(C)                                \
  private:                                                     \
    C(const C&) = delete;                                      \
    C& operator =(const C&) = delete                           \

#define CTA_MAKE_NONMOVABLE(C)                                 \
  private:                                                     \
    C(C&&) = delete;                                           \
    C& operator=(C&&) = delete                                 \

#define CTA_DEFAULT_CMP(C)                                     \
  public: auto operator<=>(const C&) const = default;          \

