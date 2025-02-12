/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_CONCEPTS_HPP
#define CALANTHA_KCORE_CONCEPTS_HPP
#include <Kernel/KCore/TypeTraits.hpp>
BEGIN_NAMESPACE(kcore);

template<typename T, typename ...Us>
concept AreAll = (IsSame<T, Us> && ...);

template<typename T, typename ...Us>
concept AnyOf = (IsSame<T, Us> || ...);

template<typename T, typename U>
concept Is = IsSame<T, U>;

template<typename T>
concept Concrete = requires { !IsReference<T>; };

template<typename T, typename ...Args>
concept ConstructibleFrom = IsDestructible<T> && IsConstructible<T, Args...>;

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::AreAll;
using kcore::AnyOf;
using kcore::Is;
using kcore::Concrete;
#endif //USING_KCORE_GLOBALLY
#endif //CALANTHA_KCORE_CONCEPTS_HPP
