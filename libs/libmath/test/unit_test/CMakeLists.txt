################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.0)

# Define unit tests as executable targets
add_executable(fixed_point_ut math/fixed_point.cpp)
target_link_libraries(fixed_point_ut PRIVATE math compiler_settings doctest::doctest)
add_test(NAME fixed_point_t COMMAND fixed_point_ut)

add_executable(integer_ut math/integer.cpp)
target_link_libraries(integer_ut PRIVATE math compiler_settings doctest::doctest)
add_test(NAME integer_t COMMAND integer_ut)

add_executable(matrix_ut math/matrix.cpp)
target_link_libraries(matrix_ut PRIVATE math compiler_settings doctest::doctest)
add_test(NAME matrix_t COMMAND matrix_ut)

add_executable(distribution_ut math/stats/distribution.cpp)
target_link_libraries(distribution_ut PRIVATE math compiler_settings doctest::doctest)
add_test(NAME distribution_t COMMAND distribution_ut)

add_executable(vector_ut math/vector.cpp)
target_link_libraries(vector_ut PRIVATE math compiler_settings doctest::doctest)
add_test(NAME vector_t COMMAND vector_ut)

add_executable(next_power_of_two_ut math/next_power_of_two.cpp)
target_link_libraries(next_power_of_two_ut PRIVATE math compiler_settings doctest::doctest)
add_test(NAME next_power_of_two_t COMMAND next_power_of_two_ut)
