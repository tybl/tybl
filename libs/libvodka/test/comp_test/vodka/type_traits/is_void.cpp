// License: The Unlicense (https://unlicense.org)
#include "vodka/type_traits/is_void.hpp"

int main() {
  static_assert(tybl::vodka::is_void_v<const void>, "const void is still void");
  static_assert(!tybl::vodka::is_void_v<volatile int>, "volatile int is not void");
}
