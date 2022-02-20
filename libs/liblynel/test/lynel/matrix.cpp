// License: The Unlicense (https://unlicense.org)
#include "lynel/matrix.hpp"

#include <doctest/doctest.h>

using tybl::lynel::matrix;

TEST_CASE("matrix::operator==()") {
  matrix<double, 3, 3> a = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  matrix<double, 3, 3> b = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  matrix<double, 3, 3> c = {1, 1, 2, 3, 4, 5, 6, 7, 8};
  matrix<double, 3, 3> d = {0, 1, 2, 3, 4, 5, 6, 7, 9};
  CHECK(a == a);
  CHECK(a == b);
  CHECK(!(a == c));
  CHECK(!(b == d));
}

TEST_CASE("aggregate initialization and correct positional assignment of values") { // NOLINT
  matrix<double, 3, 3> m = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  CHECK(m(0, 0) == 0.0);
  CHECK(m(0, 1) == 1.0);
  CHECK(m(0, 2) == 2.0);
  CHECK(m(1, 0) == 3.0);
  CHECK(m(1, 1) == 4.0);
  CHECK(m(1, 2) == 5.0);
  CHECK(m(2, 0) == 6.0);
  CHECK(m(2, 1) == 7.0);
  CHECK(m(2, 2) == 8.0);
}

TEST_CASE("scalar multiplication") {
  matrix<double, 3, 3> m = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  matrix<double, 3, 3> a = {0, 2, 4, 6, 8, 10, 12, 14, 16};
  m *= 2.0;
  CHECK(a == m);
}

TEST_CASE("transpose 3x3") {
  matrix<double, 3, 3> m = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  matrix<double, 3, 3> mt = {0, 3, 6, 1, 4, 7, 2, 5, 8};
  auto n = transpose(m);
  CHECK(n == mt);
}
