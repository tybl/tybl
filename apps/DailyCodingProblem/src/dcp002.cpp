/* Problem 002:
 * Given an array of integers, return a new array such that each element at
 * index i of the new array is the product of all the numbers in the original
 * array except the one at i. For example, if our input was [1, 2, 3, 4, 5], the
 * expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1],
 * the expected output would be [2, 3, 6].
 * Follow-up: what if you can't use division?
 */

/* Solution 002:
 * The best answer I can think of would use two passes on the numbers.
 * First, the numbers would all be multiplied
 * Second, the array would be filled in with the product divided by the number
 *  at that index.
 *
 * That solution relies on division.
 * To remove division, we could iterate over the list of n numbers n times.
 * Create the output array filled with the ones.
 * For each iteration, multiply the output index value by the ith input value
 *  unless index is equal to i.
 *
 * I'm not sure I see an efficient means to do this without division though.
 */
