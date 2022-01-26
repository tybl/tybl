// License: The Unlicense (https://unlicense.org)
#include <vodka/type_traits/is_function.hpp>

#include <doctest/doctest.h>

TEST_CASE("tybl::vodka::is_function") {
  CHECK(tybl::vodka::is_function<int(int)>::value);
  CHECK(!tybl::vodka::is_function<int>::value);
  CHECK(tybl::vodka::is_function_v<int(int)>);
  CHECK(!tybl::vodka::is_function_v<int>);
}
