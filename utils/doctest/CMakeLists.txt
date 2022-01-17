################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "v2.4.8")
FetchContent_MakeAvailable(doctest)

add_library(test_base)
target_link_libraries(test_base PUBLIC doctest::doctest)
target_sources(test_base PRIVATE src/main.cpp)
