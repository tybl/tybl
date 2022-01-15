// License: The Unlicense (https://unlicense.org)
/* Problem 001:
 * Given a list of numbers and a number k, return whether any two numbers from
 * the list add up to k. For example, given [10, 15, 3, 7] and k of 17, return
 * true since 10 + 7 is 17.
 * Bonus: Can you do this in one pass?
 */

/* Solution 001:
 * We can return true as soon as two numbers are processed that add to k.
 * Only two numbers are necessary: a and b
 * If a <= k/2, then b >= k/2
 *
 * Inputs:
 * k - target sum
 * [n:ns] - the list of numbers
 *
 * For n in [n:ns]
 *    if n <= k/2
 *      Place number in buffer in sorted order
 *    else
 *      Search sorted buffer for k - n
 */

#include <cassert>
#include <iostream>
#include <vector>

template <typename Type, typename Iter>
auto dcp001(Type p_k, Iter p_beg, Iter p_end) -> bool {
  std::vector<Type> values;
  while (p_beg != p_end) {
    if (std::binary_search(values.begin(), values.end(), p_k - *p_beg)) {
      return true;
    }
    values.insert(std::upper_bound(values.begin(), values.end(), *p_beg), *p_beg);
    ++p_beg;
  }
  return false;
}

auto main() -> int {
  std::vector<int> input = { 10, 15, 3, 7 };
  assert(dcp001(17, input.begin(), input.end()));
  std::vector<int> test_input = { 10, 15, 3, 6 };
  assert(!dcp001(17, test_input.begin(), test_input.end()));
}
