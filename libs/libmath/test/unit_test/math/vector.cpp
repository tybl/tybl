// License: The Unlicense (https://unlicense.org)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "math/vector.hpp"

#include <doctest/doctest.h>

TEST_CASE("tybl::math::vector") {
  tybl::math::vector<double,3> v;
  v(1) = 5.5;
  CHECK(v(1) == 5.5);
}
