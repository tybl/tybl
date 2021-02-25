################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(libvodka
  VERSION 0.0.9
  DESCRIPTION "Learning through reimplementing the standard library"
  LANGUAGES CXX)

option(TYBL_BUILD_ALL_TESTS "Build and run tests as a subproject" OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  include(FetchContent)
  include(util/cmake/compiler_settings.cmake)
  #include(util/cmake/Linters.cmake)

  # Use doctest as unit test framework
  FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/onqtam/doctest.git
    GIT_SHALLOW    TRUE
    GIT_TAG        "2.4.0")
  FetchContent_MakeAvailable(doctest)
endif()

add_library(vodka INTERFACE)
target_include_directories(vodka INTERFACE include)
target_sources(vodka
  INTERFACE
    include/vodka/array/array.hpp
    include/vodka/array/get.hpp
    include/vodka/array/to_array.hpp
    include/vodka/type_traits/integral_constant.hpp
    include/vodka/type_traits/remove_const.hpp
    include/vodka/type_traits/remove_cv.hpp
    include/vodka/type_traits/remove_volatile.hpp
    include/vodka/type_traits/remove_reference.hpp
    include/vodka/utility/forward.hpp
    include/vodka/utility/move.hpp)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) OR TYBL_BUILD_ALL_TESTS)
  add_subdirectory(test)
endif()
