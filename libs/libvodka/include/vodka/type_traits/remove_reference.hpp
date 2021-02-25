// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_REMOVEREFERENCE_HPP
#define TYBL_VODKA_TYPETRAITS_REMOVEREFERENCE_HPP

namespace tybl::vodka {

template <typename T>
struct remove_reference {
  using type = T;
};

template <typename T>
struct remove_reference<T&> {
  using type = T;
};

template <typename T>
struct remove_reference<T&&> {
  using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_REMOVEREFERENCE_HPP
