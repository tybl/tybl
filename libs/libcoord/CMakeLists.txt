################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(template
  VERSION 0.0.0
  DESCRIPTION "Template C++ Project using CMake"
  LANGUAGES CXX)

option(BUILD_PROJECT_TESTS "Build and run tests as a subproject" OFF)

set(IS_ROOT_PROJECT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
if(IS_ROOT_PROJECT)
  include(CTest)
endif()
include(FetchContent)
include(util/cmake/CompilerSettings.cmake)
include(util/cmake/Linters.cmake)

FetchContent_Declare(eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "3.3.7")
FetchContent_MakeAvailable(eigen)
FetchContent_Declare(units
  GIT_REPOSITORY https://github.com/nholthaus/units.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "v2.3.1")
FetchContent_MakeAvailable(units)

add_subdirectory(src)

if(IS_ROOT_PROJECT OR BUILD_PROJECT_TESTS)
  add_subdirectory(test)
endif()
