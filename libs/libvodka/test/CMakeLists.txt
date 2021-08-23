################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

add_executable(libvodka_t)
target_link_libraries(libvodka_t PRIVATE compiler_settings doctest::doctest vodka)
target_sources(libvodka_t
  PRIVATE
    src/main.cpp
    src/vodka/algorithm/max.cpp
    src/vodka/array/array.cpp
    src/vodka/functional/less_equal.cpp
    src/vodka/span/span.cpp
    src/vodka/string_view/basic_string_view.cpp
    src/vodka/type_traits/false_type.cpp
    src/vodka/type_traits/integral_constant.cpp
    src/vodka/type_traits/is_void.cpp
    src/vodka/type_traits/true_type.cpp
    src/vodka/utility/forward.cpp
)
add_test(NAME test_libvodka COMMAND libvodka_t)

