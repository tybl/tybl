// License: The Unlicense (https://unlicense.org)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "math/matrix.hpp"

#include <doctest/doctest.h>

TEST_CASE("tybl::math::matrix") {
  tybl::math::matrix<double,3,3> m;
  m(1,1) = 5.5;
  CHECK(m(1,1) == 5.5);
}
