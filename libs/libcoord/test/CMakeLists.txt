################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

add_executable(libcoord_t)
target_link_libraries(libcoord_t PRIVATE compiler_settings doctest::doctest)
target_sources(libcoord_t
  PRIVATE
    src/main.cpp
)
add_test(NAME test_libcoord COMMAND libcoord_t)
