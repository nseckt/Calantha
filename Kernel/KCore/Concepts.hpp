/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
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
concept Signed = IsIntegral<T> && IsSigned<T>;

template<typename T>
concept Unsigned = IsIntegral<T> && IsUnsigned<T>;

template<typename T>
concept Pointer = IsPointer<T>;

template<typename T>
concept Character = IsCharacter<T>;

template<typename T>
concept TrivialDTOR = IsTriviallyDestructible<T>;

template<typename T>
concept TrivialCTOR = IsTriviallyConstructible<T>;

template<typename T>
concept DefaultConstructible = IsDefaultConstructible<T>;

template<typename T, typename ...Args>
concept Constructs = IsDestructible<T> && IsConstructible<T, Args...>;

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::AreAll;
using kcore::AnyOf;
using kcore::Is;
using kcore::Concrete;
using kcore::Integer;
using kcore::Pointer;
using kcore::Character;
using kcore::Constructs;
using kcore::TrivialCTOR;
using kcore::TrivialDTOR;
using kcore::DefaultConstructible;
#endif //USING_KCORE_GLOBALLY
