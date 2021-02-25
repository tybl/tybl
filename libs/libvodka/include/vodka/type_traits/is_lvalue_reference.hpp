// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_ISLVALUEREFERENCE_HPP
#define TYBL_VODKA_TYPETRAITS_ISLVALUEREFERENCE_HPP

#include "false_type.hpp"
#include "true_type.hpp"

namespace tybl::vodka {

template <typename T>
struct is_lvalue_reference
  : false_type {};

template <typename T>
struct is_lvalue_reference<T&>
  : true_type {};

template <typename T>
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_ISLVALUEREFERENCE_HPP
