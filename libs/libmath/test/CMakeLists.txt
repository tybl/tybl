################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

add_executable(libmath_t)
target_link_libraries(libmath_t PRIVATE compiler_settings math test_base)
target_sources(libmath_t
  PRIVATE
    src/math/fixed_point.cpp
    src/math/integer.cpp
    src/math/next_power_of_two.cpp
    src/math/stats/distribution.cpp
)

add_test(NAME test_libmath COMMAND libmath_t)
