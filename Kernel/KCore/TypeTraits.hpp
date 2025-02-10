/*
* Copyright (c) 2025 Diago Lima and the Calantha contributors
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CALANTHA_KCORE_TYPETRAITS_HPP
#define CALANTHA_KCORE_TYPETRAITS_HPP
BEGIN_NAMESPACE(kcore);

template<typename...>
using VoidType = void;

template<typename T, typename = void>
struct AddReference_ {
  using LvalueType = T;
  using TvalueType = T;
};

template<typename T>
struct AddReference_<T, VoidType<T&>> {
  using LvalueType = T&;
  using RvalueType = T&&;
};

template<typename T>
using AddConst = T const;

template<typename T>
using AddPtr = T*;

template<typename T>
using AddLvalueReference = typename AddReference_<T>::LvalueType;

template<typename T>
using AddRvalueReference = typename AddReference_<T>::RvalueType;

template<typename T>
typename AddReference_<T>::RvalueType declval();

template<typename T>
struct RemoveReference_ {
  using Type = T;
};

template<typename T>
struct RemoveReference_<T&> {
  using Type = T;
};

template<typename T>
struct RemoveReference_<T&&> {
  using Type = T;
};

template<typename T>
struct RemovePointer_ {
  using Type = T;
};

template<typename T>
struct RemovePointer_<T*> {
  using Type = T;
};

template<typename T>
struct RemoveConst_ {
  using Type = T;
};

template<typename T>
struct RemoveConst_<T const> {
  using Type = T;
};

template<typename T>
using RemoveConst = typename RemoveConst_<T>::Type;

template<typename T>
using RemoveReference = typename RemoveReference_<T>::Type;

template<typename T>
using RemovePointer = typename RemovePointer_<T>::Type;

template<typename T>
struct RemoveVolatile_ {
  using Type = T;
};

template<typename T>
struct RemoveVolatile_<T volatile> {
  using Type = T;
};

template<typename T>
using RemoveVolatile = typename RemoveVolatile_<T>::Type;

template<typename T>
using RemoveCV = RemoveVolatile<RemoveConst<T>>;

template<typename T>
using Decay = RemoveReference<RemoveCV<T>>;

template<typename T>
using Underlying = __underlying_type(T);

template<typename T, typename U>
inline constexpr bool IsSame = false;

template<typename T>
inline constexpr bool IsSame<T, T> = true;

template<typename T>
inline constexpr bool IsDestructible = requires { declval<T>().~T(); };

template<typename T, typename ...Args>
inline constexpr bool IsConstructible = requires { T{ declval<Args>... }; };

template<typename T>
inline constexpr bool IsTriviallyDestructible = __has_trivial_destructor(T) && IsDestructible<T>;

template<typename T, typename ...Args>
inline constexpr bool IsTriviallyConstructible = __is_trivially_constructible(T, Args...);

template<typename T>
inline constexpr bool IsAbstract = __is_abstract(T);

END_NAMESPACE(kcore);
#endif //CALANTHA_KCORE_TYPETRAITS_HPP
