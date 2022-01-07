################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

add_executable(json_t)
target_link_libraries(json_t PRIVATE compiler_settings json test_base)
target_sources(json_t
  PRIVATE
    src/main.cpp
)

add_test(NAME test_json COMMAND json_t)
