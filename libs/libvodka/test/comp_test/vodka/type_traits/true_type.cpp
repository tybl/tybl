// License: The Unlicense (https://unlicense.org)
#include "vodka/type_traits/true_type.hpp"

void build_true_type() {
  static_assert(tybl::vodka::true_type::value, "true_type should be true");
}
