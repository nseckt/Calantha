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

END_NAMESPACE(kcore);
#endif //CALANTHA_KCORE_CONCEPTS_HPP
