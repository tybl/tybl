################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

add_executable(lynel_t)
target_link_libraries(lynel_t PRIVATE compiler_settings doctest::doctest lynel)
target_sources(lynel_t
  PRIVATE
    src/lynel/matrix.cpp
    src/lynel/vector.cpp
    src/main.cpp
)
