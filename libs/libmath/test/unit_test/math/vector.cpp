// License: The Unlicense (https://unlicense.org)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "math/lynel/vector.hpp"

#include <doctest/doctest.h>

TEST_CASE("tybl::math::vector") {
  tybl::math::lynel::vector<double,3> v;
  v(1) = 5.5;
  CHECK(v(1) == 5.5);
}
