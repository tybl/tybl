// License: The Unlicense (https://unlicense.org)
#include <vodka/type_traits/conditional.hpp>

#include <vodka/type_traits/is_same.hpp>

#include <doctest/doctest.h>

TEST_CASE("tybl::vodka::conditional") {
  CHECK(tybl::vodka::is_same_v<tybl::vodka::conditional_t<true, double, int>, double>);
  CHECK(tybl::vodka::is_same_v<tybl::vodka::conditional_t<false, double, int>, int>);
}
