// License: The Unlicense (https://unlicense.org)
#include "vodka/algorithm/all_of.hpp"

#include "doctest/doctest.h"

#include <vector>

TEST_CASE("tybl::vodka::all_of")
{
  std::vector<int> a{5, 4, 2, 3, 1};

  CHECK(tybl::vodka::all_of(a.begin(), a.end(), [](int n){ return 0 < n; }));
  CHECK(!tybl::vodka::all_of(a.begin(), a.end(), [](int n){ return 2 < n; }));
}