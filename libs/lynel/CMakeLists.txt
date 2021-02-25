################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(lynel
  VERSION 0.0.1
  DESCRIPTION "A library for small, dense matrices and vectors"
  LANGUAGES CXX)

option(BUILD_PROJECT_TESTS "Build and run tests as a subproject" OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  include(util/cmake/compiler_settings.cmake)
  include(util/cmake/Linters.cmake)
endif()

include(FetchContent)
FetchContent_Declare(libvodka
  GIT_REPOSITORY https://github.com/tybl/libvodka.git
  GIT_SHALLOW    TRUE
  GIT_TAG        origin/main)
FetchContent_MakeAvailable(libvodka)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) OR BUILD_PROJECT_TESTS)
  add_subdirectory(test)
endif()
