################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

add_library(test_base)
target_link_libraries(test_base PUBLIC doctest::doctest)
target_sources(test_base PRIVATE src/main.cpp)
