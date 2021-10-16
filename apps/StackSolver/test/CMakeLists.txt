################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

add_executable(stacksolver_t)
target_link_libraries(stacksolver_t PRIVATE compiler_settings test_base stacksolvelib)
target_sources(stacksolver_t
  PRIVATE
    src/stacksolver.cpp
)

add_test(NAME test_stacksolver COMMAND stacksolver_t)
