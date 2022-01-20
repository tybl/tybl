// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ALGORITHM_INNERPRODUCT_HPP
#define TYBL_VODKA_ALGORITHM_INNERPRODUCT_HPP

namespace tybl::vodka {

template <typename Iter1, typename Iter2, typename Type>
constexpr Type inner_product(Iter1 first1, Iter1 last1, Iter2 first2, Type init) {
  for (; first1 != last1; ++first1, ++first2) {
    init = std::move(init) + *first1 * *first2;
  }
  return init;
} // inner_product()

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_INNERPRODUCT_HPP
