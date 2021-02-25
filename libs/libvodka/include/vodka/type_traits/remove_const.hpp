// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_REMOVECONST_HPP
#define TYBL_VODKA_TYPETRAITS_REMOVECONST_HPP

namespace tybl::vodka {

template <typename T>
struct remove_const {
  using type = T;
};

template <typename T>
struct remove_const<const T> {
  using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_REMOVECONST_HPP
