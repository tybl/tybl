// License: The Unlicense (https://unlicense.org)
#include <vodka/type_traits/is_reference.hpp>

#include <doctest/doctest.h>

TEST_CASE("tybl::vodka::is_reference") {
  CHECK(!tybl::vodka::is_reference<int>::value);
  CHECK(tybl::vodka::is_reference<int&>::value);
  CHECK(tybl::vodka::is_reference<int&&>::value);
}
