// License: The Unlicense (https://unlicense.org)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "math/linear_algebra/vector.hpp"

#include <doctest/doctest.h>

TEST_CASE("tybl::math::vector") {
  tybl::math::linear_algebra::vector<double,3> v;
  v(1) = 5.5;
  CHECK(v(1) == 5.5);
}
