// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_ENABLEIF_HPP
#define TYBL_VODKA_TYPETRAITS_ENABLEIF_HPP

namespace tybl::vodka {

template <bool, typename T = void> struct enable_if {};
template <typename T> struct enable_if<true, T> { typedef T type; };
template <bool B, typename T = void> using enable_if_t = typename enable_if<B, T>::type;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_ENABLEIF_HPP
