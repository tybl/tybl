// License: The Unlicense (https://unlicense.org)
#include "math/lynel/matrix.hpp"

#include <doctest/doctest.h>

TEST_CASE("tybl::math::matrix") {
  tybl::math::lynel::matrix<double,3,3> m;
  m(1,1) = 5.5;
  CHECK(m(1,1) == 5.5);
}
