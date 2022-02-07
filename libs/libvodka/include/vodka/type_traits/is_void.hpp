// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_ISVOID_HPP
#define TYBL_VODKA_TYPETRAITS_ISVOID_HPP

#include "remove_cv.hpp"

#include <type_traits>

namespace tybl::vodka {

template <typename T>
struct is_void : std::is_same<void, remove_cv_t<T>> {};

template <typename T>
inline constexpr bool is_void_v = is_void<T>::value;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_ISVOID_HPP
