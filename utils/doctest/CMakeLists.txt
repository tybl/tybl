################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(test_base)
target_link_libraries(test_base PUBLIC doctest::doctest)
target_sources(test_base PRIVATE src/main.cpp)
