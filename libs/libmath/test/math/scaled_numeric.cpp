// License: The Unlicense (https://unlicense.org)
#include <math/scaled_numeric.hpp>

#include <doctest/doctest.h>

#include <cstdint>

TEST_CASE("tybl::math::scaled_numeric")
{
  tybl::math::scaled_numeric<int32_t, 10> decimal(9);
}
