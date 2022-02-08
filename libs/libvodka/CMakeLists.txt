################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(vodka INTERFACE)
target_include_directories(vodka INTERFACE include)
target_sources(vodka
  INTERFACE
    include/vodka/basic_fixed_string.hpp
    include/vodka/dynarray.hpp
    include/vodka/parse_error.hpp
)

add_executable(test_libvodka)
target_link_libraries(test_libvodka PRIVATE compiler_settings vodka test_base)
target_sources(test_libvodka
  PRIVATE
    test/vodka/basic_fixed_string.cpp
)
add_test(NAME libvodka_test COMMAND test_libvodka)
