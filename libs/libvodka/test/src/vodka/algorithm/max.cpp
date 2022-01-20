// License: The Unlicense (https://unlicense.org)
#include "vodka/algorithm/max.hpp"

void compile_max() { static_assert(8 == tybl::vodka::max(3, 8), "true_type should be true"); }
