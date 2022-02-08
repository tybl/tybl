################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(vodka INTERFACE)
target_include_directories(vodka INTERFACE include)
target_sources(vodka
  INTERFACE
    include/vodka/basic_fixed_string.hpp
    include/vodka/parse_error.hpp
)

add_executable(libvodka_t)
target_link_libraries(libvodka_t PRIVATE compiler_settings vodka test_base)
target_sources(libvodka_t
  PRIVATE
    test/vodka/basic_fixed_string.cpp
)
add_test(NAME test_libvodka COMMAND libvodka_t)
