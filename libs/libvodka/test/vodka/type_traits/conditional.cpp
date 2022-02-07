// License: The Unlicense (https://unlicense.org)
#include <vodka/type_traits/conditional.hpp>

#include <doctest/doctest.h>

#include <type_traits>

TEST_CASE("tybl::vodka::conditional") {
  CHECK(std::is_same_v<tybl::vodka::conditional_t<true, double, int>, double>);
  CHECK(std::is_same_v<tybl::vodka::conditional_t<false, double, int>, int>);
}
