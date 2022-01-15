################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(libparm_t)
target_link_libraries(libparm_t
  PRIVATE
    compiler_settings
    parm
    test_base)
target_sources(libparm_t
  PRIVATE
    src/test_help.cpp)

add_test(NAME test_libparm COMMAND libparm_t)
