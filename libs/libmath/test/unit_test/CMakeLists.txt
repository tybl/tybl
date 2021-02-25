################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

# Use doctest as unit test framework
FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG        "2.4.0")
FetchContent_MakeAvailable(doctest)

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
