################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14)

add_executable(libparm_t)
target_link_libraries(libparm_t
  PRIVATE
    compiler_settings
    doctest::doctest
    parm)
target_sources(libparm_t
  PRIVATE
    src/main.cpp
    src/test_help.cpp)

add_test(NAME test_libparm COMMAND libparm_t)
