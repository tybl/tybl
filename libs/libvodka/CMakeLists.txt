################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(vodka INTERFACE)
target_include_directories(vodka INTERFACE include)
target_sources(vodka
  INTERFACE
    include/vodka/algorithm/all_of.hpp
    include/vodka/algorithm/equal.hpp
    include/vodka/algorithm/find_if_not.hpp
    include/vodka/algorithm/inner_product.hpp
    include/vodka/algorithm/max.hpp
    include/vodka/algorithm/min.hpp
    include/vodka/algorithm/transform.hpp
    include/vodka/array/array.hpp
    include/vodka/array/get.hpp
    include/vodka/array/to_array.hpp
    include/vodka/cstddef/byte.hpp
    include/vodka/functional/less.hpp
    include/vodka/functional/less_equal.hpp
    include/vodka/numeric/gcd.hpp
    include/vodka/string_view/basic_string_view.hpp
    include/vodka/type_traits/bool_constant.hpp
    include/vodka/type_traits/conditional.hpp
    include/vodka/type_traits/enable_if.hpp
    include/vodka/type_traits/false_type.hpp
    include/vodka/type_traits/integral_constant.hpp
    include/vodka/type_traits/is_bool.hpp
    include/vodka/type_traits/is_const.hpp
    include/vodka/type_traits/is_function.hpp
    include/vodka/type_traits/is_lvalue_reference.hpp
    include/vodka/type_traits/is_reference.hpp
    include/vodka/type_traits/is_same.hpp
    include/vodka/type_traits/is_void.hpp
    include/vodka/type_traits/remove_const.hpp
    include/vodka/type_traits/remove_cv.hpp
    include/vodka/type_traits/remove_reference.hpp
    include/vodka/type_traits/remove_volatile.hpp
    include/vodka/type_traits/true_type.hpp
    include/vodka/type_traits/void_t.hpp
    include/vodka/utility/forward.hpp
    include/vodka/utility/move.hpp
    include/vodka/parse_error.hpp
)

add_executable(libvodka_t)
target_link_libraries(libvodka_t PRIVATE compiler_settings vodka test_base)
target_sources(libvodka_t
  PRIVATE
    test/vodka/algorithm/all_of.cpp
    test/vodka/algorithm/inner_product.cpp
    test/vodka/algorithm/max.cpp
    test/vodka/array/array.cpp
    test/vodka/functional/less_equal.cpp
    test/vodka/span/span.cpp
    test/vodka/string_view/basic_string_view.cpp
    test/vodka/type_traits/conditional.cpp
    test/vodka/type_traits/false_type.cpp
    test/vodka/type_traits/integral_constant.cpp
    test/vodka/type_traits/is_const.cpp
    test/vodka/type_traits/is_function.cpp
    test/vodka/type_traits/is_reference.cpp
    test/vodka/type_traits/is_void.cpp
    test/vodka/type_traits/true_type.cpp
    test/vodka/utility/forward.cpp
)
add_test(NAME test_libvodka COMMAND libvodka_t)
