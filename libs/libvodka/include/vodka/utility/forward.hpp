// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_UTILITY_FORWARD_HPP
#define TYBL_VODKA_UTILITY_FORWARD_HPP

#include "vodka/type_traits/is_lvalue_reference.hpp"
#include "vodka/type_traits/remove_reference.hpp"

namespace tybl::vodka {

template <typename T>
constexpr auto
forward(remove_reference_t<T>& obj) noexcept -> T&& {
  return static_cast<T&&>(obj);
}

template <typename T>
constexpr auto
forward(remove_reference_t<T>&& obj) noexcept -> T&& {
  static_assert(!is_lvalue_reference_v<T>, "Cannot forward an rvalue as an lvalue");
  return static_cast<T&&>(obj);
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_UTILITY_FORWARD_HPP
