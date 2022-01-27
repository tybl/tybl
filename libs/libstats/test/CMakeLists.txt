################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(libstats_t)
target_link_libraries(libstats_t
  PRIVATE
    doctest::doctest
    stats)
target_sources(libstats_t
  PRIVATE
    src/main.cpp)
add_test(NAME test_libstats COMMAND libstats_t)
