// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_ISBOOL_HPP
#define TYBL_VODKA_TYPETRAITS_ISBOOL_HPP

#include "is_same.hpp"
#include "remove_cv.hpp"

namespace tybl::vodka {

template <typename T>
struct is_bool
  : is_same<bool, remove_cv_t<T>> { };

template <typename T>
inline constexpr bool is_bool_v = is_bool<T>::value;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_ISBOOL_HPP
