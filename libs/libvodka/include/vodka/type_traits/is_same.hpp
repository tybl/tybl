// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_ISSAME_HPP
#define TYBL_VODKA_TYPETRAITS_ISSAME_HPP

#include "false_type.hpp"
#include "true_type.hpp"

namespace tybl::vodka {

template <typename T, typename U>
struct is_same
  : false_type {};
 
template <typename T>
struct is_same<T, T>
  : true_type {};

template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_ISSAME_HPP
