/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/KCore/TypeTraits.hpp>
#include <Kernel/KCore/Assertions.hpp>

#define TRY(EXPR)                                                                  \
  ({                                                                               \
    auto&& temp_result_ = (EXPR);                                                  \
    static_assert(!::kcore::IsLvalueReference<decltype((EXPR).release_value())>);  \
    if(!temp_result_.has_value()) return temp_result_.release_error();             \
    temp_result_.release_value();                                                  \
  })                                                                               \

#define MUST(EXPR)                                                                 \
  ({                                                                               \
    auto&& temp_result_ = (EXPR);                                                  \
    static_assert(!::kcore::IsLvalueReference<decltype((EXPR).release_value())>);  \
    ASSERT(temp_result_.has_value(), "MUST() expression evaluated to an error!");  \
    temp_result_.release_value();                                                  \
  })                                                                               \

#define ERROR_IF(EXPR, ...) do {                                                   \
    if((EXPR)) { return ::kcore::Error{ __VA_ARGS__ }; }                           \
  } while(0)                                                                       \

#define ERROR_IF_NOT(EXPR, ...) do {                                               \
    if(!(EXPR)) { return ::kcore::Error{ __VA_ARGS__ }; }                          \
  } while(0)                                                                       \

