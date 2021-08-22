################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13) # relative path target_sources()

add_library(math)
target_include_directories(math PUBLIC include)
target_link_libraries(math PUBLIC compiler_settings)
target_sources(math
  INTERFACE
    include/math/stats/distribution.hpp
    include/math/stats/probability.hpp
    include/math/pow10.hpp
  PRIVATE
    src/math/lynel/vector.cpp
  PUBLIC
    include/math/lynel/vector.hpp
  )

add_subdirectory(test)
