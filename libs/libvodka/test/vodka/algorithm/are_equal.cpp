// License: The Unlicense (https://unlicense.org)
#include <vodka/algorithm/are_equal.hpp>

#include <doctest/doctest.h>

#include <vodka/array/array.hpp>

TEST_CASE("tybl::vodka::are_equal") {
  tybl::vodka::array<int,5> a{1, 3, 5, 7, 9};
  tybl::vodka::array<int,5> b{1, 3, 5, 7, 8};
  CHECK(tybl::vodka::are_equal(a.begin(), a.end(), a.begin()));
  CHECK(!tybl::vodka::are_equal(a.begin(), a.end(), b.begin()));
}