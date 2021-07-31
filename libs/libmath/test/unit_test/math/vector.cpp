// License: The Unlicense (https://unlicense.org)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "math/lynel/vector.hpp"
#include "math/lynel/vector_ops.hpp"

#include <doctest/doctest.h>

TEST_CASE("tybl::math::vector") {
  tybl::math::lynel::vector<double,3> v;
  v(1) = 5.5;
  CHECK(v(1) == 5.5);
}

TEST_CASE("Associative law for vector addition") {
  tybl::math::lynel::vector<double,3> a{ 1, 2, 3 };
  tybl::math::lynel::vector<double,3> b{ 4, 5, 6 };
  tybl::math::lynel::vector<double,3> c{ 7, 8, 9 };

  auto l = (a + b)+ c;
  auto r =  a +(b + c);

  CHECK(l == r);
}
