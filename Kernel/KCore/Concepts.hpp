/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_CONCEPTS_HPP
#define CALANTHA_KCORE_CONCEPTS_HPP
#include <Kernel/KCore/TypeTraits.hpp>
BEGIN_NAMESPACE(kcore);

template<typename T, typename ...Us>
concept AreAll = (IsSame<T, Decay<Us>> && ...);

template<typename T, typename ...Us>
concept AnyOf = (IsSame<T, Decay<Us>> || ...);

template<typename T, typename U>
concept Is = IsSame<T, U>;

template<typename T>
concept Concrete = requires { !IsReference<T>; };

template<typename T>
concept Integer = IsIntegral<T>;

template<typename T>
concept Pointer = IsPointer<T>;

template<typename T>
concept DefaultConstructible = IsDefaultConstructible<T>;

template<typename T>
concept Character = AnyOf<Unsigned<T>, unsigned char, char8_t, char16_t, char32_t>;

template<typename T, typename ...Args>
concept ConstructibleFrom = IsDestructible<T> && IsConstructible<T, Args...>;

END_NAMESPACE(kcore);
#endif //CALANTHA_KCORE_CONCEPTS_HPP
#ifdef USING_KCORE_GLOBALLY
using kcore::AreAll;
using kcore::AnyOf;
using kcore::Is;
using kcore::Concrete;
#endif //USING_KCORE_GLOBALLY
