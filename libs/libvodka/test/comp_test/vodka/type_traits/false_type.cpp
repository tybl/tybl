// License: The Unlicense (https://unlicense.org)
#include "vodka/type_traits/false_type.hpp"

void build_false_type() {
  static_assert(!tybl::vodka::false_type::value, "false_type should not be true");
}
