################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

# Use doctest as unit test framework
FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG        "2.3.8")
FetchContent_MakeAvailable(doctest)

# Define unittests executable target
add_executable(unit_test)
target_link_libraries(unit_test
  PRIVATE
    compile_settings
    doctest::doctest
    parm)
target_sources(unit_test
  PRIVATE
    main.cpp
    test_help.cpp)

add_test(NAME build_unit_test_t
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target unit_test)
set_tests_properties(build_unit_test_t
  PROPERTIES FIXTURES_SETUP unit_test_tf)

add_test(NAME run_unit_test_t COMMAND unit_test)
set_tests_properties(run_unit_test_t
  PROPERTIES FIXTURES_REQUIRED unit_test_tf)
