// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ARRAY_GET_HPP
#define TYBL_VODKA_ARRAY_GET_HPP

#include "vodka/utility/move.hpp"

namespace tybl::vodka {

// get<>

template <size_t I, typename T, size_t N>
constexpr auto
get(array<T, N>& a) noexcept -> T& {
  static_assert(I < N, "Index out of bounds in get<>(array)");
  return a.m_elems[I];
}

template <size_t I, typename T, size_t N>
constexpr auto
get(array<T, N> const& a) noexcept -> T const& {
  static_assert(I < N, "Index out of bounds in get<>(const array)");
  return a.m_elems[I];
}

template <size_t I, typename T, size_t N>
constexpr auto
get(array<T, N>&& a) noexcept -> T&& {
  static_assert(I < N, "Index out of bounds in get<>(array&&)");
  return utility::move(a.m_elems[I]);
}

template <size_t I, typename T, size_t N>
constexpr auto
get(array<T, N> const&& a) noexcept -> T const&& {
  static_assert(I < N, "Index out of bounds in get<>(const array&&)");
  return utility::move(a.m_elems[I]);
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ARRAY_GET_HPP
