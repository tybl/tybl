// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_ALGORITHM_TRANSFORM_HPP
#define TYBL_VODKA_ALGORITHM_TRANSFORM_HPP

namespace tybl::vodka {

template <typename InIt1, class InIt2, class OutIt, class BinaryOp>
constexpr OutIt transform(InIt1 aBeg, InIt1 aEnd, InIt2 bBeg, OutIt dest, BinaryOp biOp) {
  for (; aBeg != aEnd; ++aBeg, ++bBeg, ++dest) {
    *dest = biOp(*aBeg, *bBeg);
  }
  return dest;
}

} // namespace tybl::vodka

#endif // TYBL_VODKA_ALGORITHM_TRANSFORM_HPP
