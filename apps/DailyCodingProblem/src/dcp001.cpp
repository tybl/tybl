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
bool dcp001(Type k, Iter beg, Iter end) {
  std::vector<Type> values;
  while (beg != end) {
    if (std::binary_search(values.begin(), values.end(), k - *beg)) {
      return true;
    }
    values.insert(std::upper_bound(values.begin(), values.end(), *beg), *beg);
    ++beg;
  }
  return false;
}

int main() {
  std::vector<int> input = { 10, 15, 3, 7 };
  assert(dcp001(17, input.begin(), input.end()));
  std::vector<int> test_input = { 10, 15, 3, 6 };
  assert(!dcp001(17, test_input.begin(), test_input.end()));
}
