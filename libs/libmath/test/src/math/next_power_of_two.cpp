// License: The Unlicense (https://unlicense.org)
#include "math/next_power_of_two.hpp"

#include "doctest/doctest.h"

TEST_CASE_TEMPLATE("Try some values", T, char, short, int, long) {
  CHECK(static_cast<T>(0) == tybl::math::next_power_of_two<T>(static_cast<T>(0)));
  CHECK(static_cast<T>(0) == tybl::math::next_power_of_two<T>(static_cast<T>(-1)));
  CHECK(static_cast<T>(1) == tybl::math::next_power_of_two<T>(static_cast<T>(1)));
  CHECK(static_cast<T>(2) == tybl::math::next_power_of_two<T>(static_cast<T>(2)));
  CHECK(static_cast<T>(4) == tybl::math::next_power_of_two<T>(static_cast<T>(3)));
  CHECK(static_cast<T>(4) == tybl::math::next_power_of_two<T>(static_cast<T>(4)));
  CHECK(static_cast<T>(8) == tybl::math::next_power_of_two<T>(static_cast<T>(5)));
  CHECK(static_cast<T>(8) == tybl::math::next_power_of_two<T>(static_cast<T>(6)));
  CHECK(static_cast<T>(8) == tybl::math::next_power_of_two<T>(static_cast<T>(7)));
  CHECK(static_cast<T>(8) == tybl::math::next_power_of_two<T>(static_cast<T>(8)));
  CHECK(static_cast<T>(16) == tybl::math::next_power_of_two<T>(static_cast<T>(9)));
  CHECK(static_cast<T>(16) == tybl::math::next_power_of_two<T>(static_cast<T>(10)));
  CHECK(static_cast<T>(16) == tybl::math::next_power_of_two<T>(static_cast<T>(11)));
  CHECK(static_cast<T>(32) == tybl::math::next_power_of_two<T>(static_cast<T>(17)));
}
