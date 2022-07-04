// License: The Unlicense (https://unlicense.org)
#include <math/scaled_numeric.hpp>

#include <doctest/doctest.h>

#include <cstdint>

TEST_CASE("tybl::math::scaled_numeric")
{
  const double value = 9.0;
  tybl::math::scaled_numeric<int32_t, 100> decimal(value);
  CHECK(static_cast<double>(decimal) == value);
  CHECK(decimal.rep() == 900);
}
