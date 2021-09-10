################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

add_executable(linal_t)
target_link_libraries(linal_t PRIVATE compiler_settings test_base linal vodka)
target_sources(linal_t
  PRIVATE
    src/books/LinearAlgebra_TheoryIntuitionCode.cpp
    src/linal/matrix.cpp
)

add_test(NAME test_linal COMMAND linal_t)
