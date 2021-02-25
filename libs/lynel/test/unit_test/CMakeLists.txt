################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

# Use doctest as unit test framework
FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "2.3.8")
FetchContent_MakeAvailable(doctest)

# Define unittests executable target
add_executable(unit_test)
target_link_libraries(unit_test
  PRIVATE
    compiler_settings
    vodka
    doctest::doctest)
target_sources(unit_test
  PRIVATE
    lynel/array_vector.cpp
    main.cpp)
add_test(NAME unit_test_t COMMAND unit_test)
