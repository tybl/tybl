// License: The Unlicense (https://unlicense.org)
#include "math/next_power_of_two.hpp"

#include "doctest/doctest.h"

TEST_CASE_TEMPLATE("Try all the types!", T, bool, char, short, int, long) {
  CHECK(static_cast<T>(0) == tybl::math::next_power_of_two<T>(static_cast<T>(0)));
}
