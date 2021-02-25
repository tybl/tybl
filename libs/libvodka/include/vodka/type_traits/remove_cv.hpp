// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_REMOVECV_HPP
#define TYBL_VODKA_TYPETRAITS_REMOVECV_HPP

namespace tybl::vodka {

template <typename T>
struct remove_cv {
  using type = T;
};

template <typename T>
struct remove_cv<const T> {
  using type = T;
};

template <typename T>
struct remove_cv<volatile T> {
  using type = T;
};

template <typename T>
struct remove_cv<const volatile T> {
  using type = T;
};

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_REMOVECV_HPP
