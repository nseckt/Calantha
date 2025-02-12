/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_MACROUTILS_HPP
#define CALANTHA_MACROUTILS_HPP

#define CTA_MACRO_STRINGIFY(X) #X
#define CTA_MACRO_TOSTRING(X) CTA_MACRO_STRINGIFY(X)
#define SOURCE_LOC __FILE__ ":" CTA_MACRO_TOSTRING(__LINE__)

#define CTA_EXPAND_SAFE_IF(COND, ...) do{ if( COND ) __VA_ARGS__ }while(false);
#define CTA_MACRO_CONCAT_IMPL_(X, Y) X##Y
#define CTA_MACRO_CONCAT(X, Y) N19_MACRO_CONCAT_IMPL_(X, Y)
#define CTA_UNIQUE_NAME(X) N19_MACRO_CONCAT(X, __COUNTER__)

#endif //CALANTHA_MACROUTILS_HPP
