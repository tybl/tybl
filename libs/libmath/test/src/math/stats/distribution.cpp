// License: The Unlicense (https://unlicense.org)
#include "math/stats/distribution.hpp"

#include <doctest/doctest.h>

TEST_CASE("tybl::math::stats::distribution") {
  tybl::math::stats::distribution<int64_t> accum;
  for (int64_t i = 0; i < 100; ++i) {
    accum += i;
    accum += -i;
    CHECK(accum.mean() < 0.000001);
  }
  CHECK(accum.minimum() == -99);
  CHECK(accum.maximum() == 99);
}
