/*
* Copyright (c) 2025 Diago Lima
* SPDX-License-Identifier: BSD-3-Clause
*/

#pragma once
#include <Kernel/KCore/Types.hpp>
#include <Kernel/KCore/TypeManip.hpp>
#include <Kernel/KCore/Concepts.hpp>
BEGIN_NAMESPACE(kcore);

///
/// NthTypeAccessor --
/// Access the nth type from a given pack Types as NthTypeAccessor::Type.
template<usize n, typename ...Types>
struct NthTypeAccessor;

template<usize n, typename T, typename ...Types>
struct NthTypeAccessor<n, T, Types...> {
  using Type = typename NthTypeAccessor<n - 1, Types...>::Type;
};

template<typename T, typename ...Types>
struct NthTypeAccessor<0, T, Types...> {
  using Type = T;
};

///
/// Helper type alias for NthTypeAccessor
template<usize n, typename ...Types>
using NthType = typename NthTypeAccessor<n, Types...>::Type;

///
/// TupleStorage -- recursive storage helper for the main Tuple class.
/// Tuple uses this to recursively define data fields with a
/// user-provided pack of types.
template<typename ...Tail>
struct TupleStorage;

template<typename T, typename ...Tail>
struct TupleStorage<T, Tail...> {
  constexpr TupleStorage() = default;
  ~TupleStorage() = default;

  TupleStorage(T&& head, Tail&&... tail)
  : head_(kcore::move(head)), tail_(kcore::move(tail)...) {}

  TupleStorage(const T& head, const Tail&... tail)
  : head_(head), tail_(tail...) {}

  template<typename ...OTs>
  TupleStorage(const TupleStorage<OTs...>& other)
  : head_(other.head_), tail_(other.tail_) {}

  template<typename ...OTs>
  TupleStorage(TupleStorage<OTs...>&& other)
  : head_(kcore::move(other.head_)), tail_(kcore::move(other.tail_)) {}

  T head_;
  TupleStorage<Tail...> tail_;
};

template<>
struct TupleStorage<> {
  constexpr TupleStorage() = default;
  ~TupleStorage() = default;
};

///
/// NthItemAccessor --
/// Access the nth item inside of a TupleStorage with a given
/// pack of types Types.
template<usize n, typename ...Types>
struct NthItemAccessor;

template<usize n, typename T, typename ...Types>
struct NthItemAccessor<n, T, Types...> {
  static auto access(const TupleStorage<T, Types...>& store) -> const NthType<n - 1, Types...>& {
    return NthItemAccessor<n - 1, Types...>::access(store.tail_);
  }

  static auto access(TupleStorage<T, Types...>& store) -> NthType<n - 1, Types...>& {
    return NthItemAccessor<n - 1, Types...>::access(store.tail_);
  }
};

template<typename T, typename ...Types>
struct NthItemAccessor<0, T, Types...> {
  static auto access(TupleStorage<T, Types...>& store) -> T& {
    return store.head_;
  }

  static auto access(const TupleStorage<T, Types...>& store) -> const T& {
    return store.head_;
  }
};

template<typename ...Types>
class Tuple /* Tuple Implementation -- */ {
public:
  template<typename ...OTs>
  friend class Tuple;

  template<usize n, typename ...OTs>
  struct ConstructibleWith_ {
    static constexpr bool value
      = kcore::IsConstructible<NthType<n, Types...>, NthType<n, OTs...>>
      && ConstructibleWith_<n - 1, OTs...>::value;
  };

  template<typename ...OTs>
  struct ConstructibleWith_<0, OTs...> {
    static constexpr bool value
      = kcore::IsConstructible<NthType<0, Types...>, NthType<0, OTs...>>;
  };

  template<usize i> NODISCARD_
  typename NthTypeAccessor<i, Types...>::Type& get() {
    static_assert(i < sizeof...(Types), "Out of bounds tuple access!");
    return NthItemAccessor<i, Types...>::access(store_);
  }

  template<usize i> NODISCARD_
  const typename NthTypeAccessor<i, Types...>::Type& get() const {
    static_assert(i < sizeof...(Types), "Out of bounds tuple access!");
    return NthItemAccessor<i, Types...>::access(store_);
  }

  template<typename ...OTs>
    requires ConstructibleWith_<sizeof...(OTs) - 1, OTs...>::value
  Tuple(const Tuple<OTs...>& other) : store_(other.store_) {}

  template<typename ...OTs>
    requires ConstructibleWith_<sizeof...(OTs) - 1, OTs...>::value
  Tuple(Tuple<OTs...>&& other) noexcept : store_(kcore::move(other.store_)) {}

  template<typename ...OTs>
    requires (sizeof...(OTs) > 0 && ConstructibleWith_<sizeof...(OTs) - 1, OTs...>::value)
  Tuple(OTs&&... args) : store_(kcore::forward<OTs>(args)...) {}

 ~Tuple() = default;
  Tuple() = default;
private:
  TupleStorage<Types...> store_;
};

///
/// Helper functions for creating and manipulating tuples.
template<typename ...Args>
auto make_tuple(Args&&... args) -> Tuple<RemoveReference<Args>...> {
  return Tuple<RemoveReference<Args>...>{ kcore::forward<Args>(args)... };
}

template<usize n, typename ...Args>
auto tuple_accessor(const Tuple<Args...>& tup) -> const NthType<n, Args...>& {
  return tup. template get<n>();
}

template<usize n, typename ...Args>
auto tuple_accessor(Tuple<Args...>&& tup) -> NthType<n, Args...>&& {
  return kcore::move(tup. template get<n>());
}

END_NAMESPACE(kcore);