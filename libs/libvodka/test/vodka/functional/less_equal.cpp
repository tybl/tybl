// License: The Unlicense (https://unlicense.org)
#include "vodka/functional/less_equal.hpp"

void build_less_equal() { static_assert(tybl::vodka::less_equal()(8.0, 8), "Eight is equat to eight"); }
