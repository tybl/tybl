################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14)

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

add_test(NAME run_unit_test_t COMMAND unit_test)
