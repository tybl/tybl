// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_MATH_POW10_HPP
#define TYBL_MATH_POW10_HPP

#include <cstdint>

namespace tybl::math {

constexpr auto pow10(uint32_t p_exponent) -> int64_t { return (p_exponent == 0) ? 1 : (10 * pow10(p_exponent - 1)); }

} // namespace tybl::math

#endif // TYBL_MATH_POW10_HPP
