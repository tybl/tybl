// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_ENABLEIF_HPP
#define TYBL_VODKA_TYPETRAITS_ENABLEIF_HPP

namespace tybl::vodka {

template <bool, typename TrueType = void>
struct enable_if {};

template <typename TrueType>
struct enable_if<true, TrueType> {
  using type = TrueType;
};

template <bool B, typename TrueType = void>
using enable_if_t = typename enable_if<B, TrueType>::type;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_ENABLEIF_HPP
