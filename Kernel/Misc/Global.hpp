/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_GLOBAL_HPP
#define CALANTHA_GLOBAL_HPP

// This file contains macros included into every compilation unit.
// Try to avoid bloating this file so we don't increase compile times.

#define VGA_TEXTMODE_ 1
#define BEGIN_NAMESPACE(NAME) namespace NAME {
#define END_NAMESPACE(NAME) }
#define PAGESIZE 4096

#define CTA_EXPAND_SAFE_IF(COND, ...) do{ if( COND ) __VA_ARGS__ }while(false);
#define CTA_MACRO_CONCAT_IMPL_(X, Y) X##Y
#define CTA_MACRO_CONCAT(X, Y) N19_MACRO_CONCAT_IMPL_(X, Y)
#define CTA_UNIQUE_NAME(X) N19_MACRO_CONCAT(X, __COUNTER__)

#endif //CALANTHA_GLOBAL_HPP
