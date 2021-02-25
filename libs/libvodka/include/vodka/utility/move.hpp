// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_UTILITY_MOVE_HPP
#define TYBL_VODKA_UTILITY_MOVE_HPP

#include "vodka/type_traits/remove_reference.hpp" // remove_reference

namespace tybl::vodka {

template <typename T>
constexpr auto
move(T&& obj) noexcept -> remove_reference_t<T>&& {
  return static_cast<remove_reference_t<T>&&>(obj);
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_UTILITY_MOVE_HPP
