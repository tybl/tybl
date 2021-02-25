// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ARRAY_TOARRAY_HPP
#define TYBL_VODKA_ARRAY_TOARRAY_HPP

#include "vodka/type_traits/remove_cv.hpp"
#include "vodka/utility/move.hpp"

#include <type_traits> // std::is_*_constructable_v, std::is_array
#include <utility>     // std::index_sequence, std::make_index_sequence

namespace tybl::vodka {

// to_array

template <typename T, size_t N, size_t... I>
constexpr auto
impl_lvalue_to_array(T (&a)[N], std::index_sequence<I...> /*indices*/) -> array<type_traits::remove_cv_t<T>, N> {
  return {{a[I]...}};
}

template <typename T, size_t N>
constexpr auto
to_array(T (&a)[N]) noexcept(std::is_nothrow_constructible_v<T, T&>) -> array<type_traits::remove_cv_t<T>, N> {
  static_assert(!std::is_array_v<T>, "[array.creation]/1: to_array does not accept multidimensional arrays.");
  static_assert(std::is_constructible_v<T, T&>, "[array.creation]/1: to_array requires copy constructible elements.");
  return impl_lvalue_to_array(a, std::make_index_sequence<N>());
}

template <typename T, size_t N, size_t... I>
constexpr auto
impl_rvalue_to_array(T(&&a)[N], std::index_sequence<I...> /*indices*/) -> array<type_traits::remove_cv_t<T>, N> {
  return {{utility::move(a[I])...}};
}

template <typename T, size_t N>
constexpr auto
to_array(T(&&a)[N]) noexcept(std::is_nothrow_move_constructible_v<T>) -> array<type_traits::remove_cv_t<T>, N> {
  static_assert(!std::is_array_v<T>, "[array.creation]/4: to_array does not accept multidimensional arrays.");
  static_assert(std::is_move_constructible_v<T>, "[array.creation]/4: to_array requires move constructible elements.");
  return impl_rvalue_to_array(utility::move(a), std::make_index_sequence<N>());
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ARRAY_TOARRAY_HPP
