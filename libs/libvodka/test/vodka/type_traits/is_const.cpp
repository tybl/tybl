// License: The Unlicense (https://unlicense.org)
#include <vodka/type_traits/is_const.hpp>

#include <doctest/doctest.h>

TEST_CASE("tybl::vodka::is_const") {
  CHECK(tybl::vodka::is_const<const int>::value);
  CHECK(!tybl::vodka::is_const<int>::value);
  CHECK(tybl::vodka::is_const_v<const int>);
  CHECK(!tybl::vodka::is_const_v<int>);
}
