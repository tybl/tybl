// License: The Unlicense (https://unlicense.org)
#include <vodka/numeric/gcd.hpp>

#include <doctest/doctest.h>

TEST_CASE("tybl::vodka::gcd()") {
  CHECK(123 == tybl::vodka::gcd(123,123));
  CHECK(1 == tybl::vodka::gcd(97,103));
  CHECK(64 == tybl::vodka::gcd(128,192));
}
