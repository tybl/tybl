################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(tybl
	VERSION 0.0.0
	DESCRIPTION "Collection of C++ libraries, applications and tools written by me"
	LANGUAGES CXX)

include(CTest)
include(FetchContent)
include(utils/cmake/CompilerSettings.cmake)
include(utils/cmake/Linters.cmake)

# Use doctest as unit test framework
FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG        "2.4.6")
FetchContent_MakeAvailable(doctest)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_subdirectory(utils/doctest)
add_subdirectory(libs)
add_subdirectory(apps)
