// License: The Unlicense (https://unlicense.org)
#include "vodka/algorithm/max.hpp"

void build_true_type() {
  static_assert(8 == tybl::vodka::max(3,8), "true_type should be true");
}
