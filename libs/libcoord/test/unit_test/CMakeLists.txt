################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

# Use doctest as unit test framework
FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "2.4.0")
FetchContent_MakeAvailable(doctest)

# Define unittests executable target
add_executable(unit_test main.cpp)
target_link_libraries(unit_test PRIVATE compiler_settings doctest::doctest)
add_test(NAME unit_test_t COMMAND unit_test)
