// License: The Unlicense (https://unlicense.org)
#include "lynel/matrix.hpp"

#include <doctest/doctest.h>

using namespace tybl::lynel;

TEST_CASE("tybl::lynel::matrix") {
  matrix<double,3,3> m;
  m(1,1) = 5.5;
  CHECK(m(1,1) == 5.5);
}

TEST_CASE("aggregate initialization and correct positional assignment of values") {
  matrix<double,3,3> m = {
    0,1,2,
    3,4,5,
    6,7,8
  };
  CHECK(m(0,0) == 0.0);
  CHECK(m(0,1) == 1.0);
  CHECK(m(0,2) == 2.0);
  CHECK(m(1,0) == 3.0);
  CHECK(m(1,1) == 4.0);
  CHECK(m(1,2) == 5.0);
  CHECK(m(2,0) == 6.0);
  CHECK(m(2,1) == 7.0);
  CHECK(m(2,2) == 8.0);
}
