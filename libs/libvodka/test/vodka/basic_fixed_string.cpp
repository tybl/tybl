// License: The Unlicense (https://unlicense.org)
#include <vodka/basic_fixed_string.hpp>

#include <doctest/doctest.h>

TEST_CASE("tybl::vodka::basic_fixed_string") {
  auto fs = static_cast<tybl::vodka::basic_fixed_string>("Hello");
  CHECK(fs.size() == 5);
}
