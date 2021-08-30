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

TEST_CASE("scalar multiplication") {
  matrix<double,3,3> m = {
    0,1,2,
    3,4,5,
    6,7,8
  };
  m *= 2.0;
  CHECK(m(0,0) == 0.0);
  CHECK(m(0,1) == 2.0);
  CHECK(m(0,2) == 4.0);
  CHECK(m(1,0) == 6.0);
  CHECK(m(1,1) == 8.0);
  CHECK(m(1,2) == 10.0);
  CHECK(m(2,0) == 12.0);
  CHECK(m(2,1) == 14.0);
  CHECK(m(2,2) == 16.0);
}

TEST_CASE("transpose 3x3") {
  matrix<double,3,3> m = {
    0,1,2,
    3,4,5,
    6,7,8
  };
  auto n = transpose(m);
  CHECK(n(0,0) == m(0,0));
  CHECK(n(1,0) == m(0,1));
  CHECK(n(2,0) == m(0,2));
  CHECK(n(0,1) == m(1,0));
  CHECK(n(1,1) == m(1,1));
  CHECK(n(2,1) == m(1,2));
  CHECK(n(0,2) == m(2,0));
  CHECK(n(1,2) == m(2,1));
  CHECK(n(2,2) == m(2,2));
}
