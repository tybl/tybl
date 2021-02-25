################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(math
  VERSION 0.0.1
  DESCRIPTION "My math library"
  LANGUAGES CXX)

# Variables
option(BUILD_ALL_TESTS "Build and run tests as a subproject" OFF)
set(IS_ROOT_PROJECT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

# Includes
if(IS_ROOT_PROJECT)
  include(CTest)
endif()
include(FetchContent)
include(util/cmake/CompilerSettings.cmake)
include(util/cmake/Linters.cmake)

add_library(math INTERFACE)
target_compile_features(math INTERFACE cxx_static_assert)
target_include_directories(math INTERFACE include)
target_sources(math
  INTERFACE
    include/math/stats/distribution.hpp
    include/math/stats/probability.hpp
    include/math/pow10.hpp)

if(IS_ROOT_PROJECT OR BUILD_ALL_TESTS)
  add_subdirectory(test)
endif()
