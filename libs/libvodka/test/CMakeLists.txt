################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(libvodka_t)
target_link_libraries(libvodka_t PRIVATE compiler_settings vodka test_base)
target_sources(libvodka_t
  PRIVATE
    vodka/algorithm/all_of.cpp
    vodka/algorithm/inner_product.cpp
    vodka/algorithm/max.cpp
    vodka/array/array.cpp
    vodka/functional/less_equal.cpp
    vodka/span/span.cpp
    vodka/string_view/basic_string_view.cpp
    vodka/type_traits/conditional.cpp
    vodka/type_traits/false_type.cpp
    vodka/type_traits/integral_constant.cpp
    vodka/type_traits/is_const.cpp
    vodka/type_traits/is_function.cpp
    vodka/type_traits/is_reference.cpp
    vodka/type_traits/is_void.cpp
    vodka/type_traits/true_type.cpp
    vodka/utility/forward.cpp
)
add_test(NAME test_libvodka COMMAND libvodka_t)

