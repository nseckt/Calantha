/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/KCore/TypeTraits.hpp>
BEGIN_NAMESPACE(kcore);

template<typename T>
NODISCARD_ constexpr auto to_underlying(T&& t) {
  return static_cast<UnderlyingType<Decay<T>>>( t );
}

template<typename T>
NODISCARD_ constexpr auto forward(RemoveReference<T>& param) -> T&& {
  return static_cast<T&&>(param);
}

template<typename T>
NODISCARD_ constexpr auto forward(RemoveReference<T>&& param) -> T&& {
  static_assert(!IsLvalueReference<T>, "Trying to forward an rvalue as an lvalue!");
  return static_cast<T&&>(param);
}

template<typename T>
NODISCARD_ constexpr auto move(T&& obj) -> RemoveReference<T>&& {
  return static_cast<RemoveReference<T>&&>(obj);
}

template<typename T>
NODISCARD_ constexpr auto cref(T&& obj) -> const RemoveReference<T>& {
  return static_cast<const RemoveReference<T>&>(obj);
}

END_NAMESPACE(kcore);
#ifdef USING_KCORE_GLOBALLY
using kcore::to_underlying;
using kcore::forward;
using kcore::move;
using kcore::cref;
#endif //USING_KCORE_GLOBALLY
