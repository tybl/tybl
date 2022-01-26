// License: The Unlicense (https://unlicense.org)
#include "vodka/algorithm/inner_product.hpp"

#include <vector>

void compile_inner_product() {
  std::vector<int> a{0, 1, 2, 3, 4};
  std::vector<int> b{5, 4, 2, 3, 1};

  int r1 = tybl::vodka::inner_product(a.begin(), a.end(), b.begin(), 0);
}