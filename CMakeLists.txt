################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(tybl
	VERSION 0.0.0
	DESCRIPTION "Collection of C++ libraries, applications and tools written by me"
	LANGUAGES CXX)

include(CTest)
include(utils/cmake/CompilerSettings.cmake)
include(utils/cmake/external_libraries.cmake)
include(utils/cmake/Linters.cmake)

add_subdirectory(utils/doctest)
add_subdirectory(libs)
add_subdirectory(apps)
