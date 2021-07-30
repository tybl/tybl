################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

add_library(math INTERFACE)
target_compile_features(math INTERFACE cxx_static_assert)
target_include_directories(math INTERFACE include)
target_sources(math
  INTERFACE
    include/math/stats/distribution.hpp
    include/math/stats/probability.hpp
    include/math/pow10.hpp)

add_subdirectory(test)
