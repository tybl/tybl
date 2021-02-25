// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_FUNCTIONAL_LESS_HPP
#define TYBL_VODKA_FUNCTIONAL_LESS_HPP

#include "vodka/utility/forward.hpp"

// Relevant links:

namespace tybl::vodka {

template <typename T = void>
struct less {

  [[nodiscard]] constexpr auto
  operator()(T const& lhs, T const& rhs) const -> bool {
    return lhs < rhs;
  }

};

template <>
struct less<void> {

  using is_transparent = void;

  template <typename TypeL, typename TypeR>
  [[nodiscard]] constexpr auto
  operator()(TypeL&& lhs, TypeR&& rhs) const
    noexcept(noexcept(forward<TypeL>(lhs) < forward<TypeR>(rhs)))
    ->       decltype(forward<TypeL>(lhs) < forward<TypeR>(rhs))
  {
    return            forward<TypeL>(lhs) < forward<TypeR>(rhs);
  }

};

} // namespace tybl::vodka

#endif // TYBL_VODKA_FUNCTIONAL_LESS_HPP
