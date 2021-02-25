################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(parm
  VERSION 0.0.0
  DESCRIPTION "Command-line interface argument wrangler"
  LANGUAGES CXX)

option(PARM_BUILD_TESTS "Build and run parm tests as a subproject" OFF)

set(IS_ROOT_PROJECT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

if(IS_ROOT_PROJECT)
  include(CTest)
endif()
include(FetchContent)

add_library(parm INTERFACE)
target_include_directories(parm INTERFACE include)
target_sources(parm
  INTERFACE
    include/parm/Application.hpp
    include/parm/Parameter.hpp)

if(IS_ROOT_PROJECT OR PARM_BUILD_TESTS)
  add_subdirectory(test EXCLUDE_FROM_ALL)
endif()
