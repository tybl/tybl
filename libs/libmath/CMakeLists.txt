################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(math INTERFACE)
target_include_directories(math INTERFACE include)
target_link_libraries(math INTERFACE compiler_settings)
target_sources(math
  INTERFACE
    include/math/stats/distribution.hpp
    include/math/stats/probability.hpp
    include/math/pow10.hpp
)

add_executable(libmath_t)
target_link_libraries(libmath_t PRIVATE compiler_settings math test_base)
target_sources(libmath_t
  PRIVATE
    test/math/fixed_point.cpp
    test/math/integer.cpp
    test/math/next_power_of_two.cpp
    test/math/stats/distribution.cpp
)

add_test(NAME test_libmath COMMAND libmath_t)
