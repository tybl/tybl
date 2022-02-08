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

add_executable(test_libmath)
target_link_libraries(test_libmath PRIVATE compiler_settings math test_base)
target_sources(test_libmath
  PRIVATE
    test/math/fixed_point.cpp
    test/math/integer.cpp
    test/math/next_power_of_two.cpp
    test/math/stats/distribution.cpp
)

add_test(NAME libmath_test COMMAND test_libmath)
