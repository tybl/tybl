// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_TYPETRAITS_BOOLCONSTANT_HPP
#define TYBL_VODKA_TYPETRAITS_BOOLCONSTANT_HPP

#include "integral_constant.hpp"

namespace tybl::vodka {

template <bool _Val>
using bool_constant = integral_constant<bool, _Val>;

} // namespace tybl::vodka

#endif // TYBL_VODKA_TYPETRAITS_INTEGRALCONSTANT_HPP

