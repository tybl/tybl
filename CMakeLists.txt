################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(tybl
	VERSION 0.0.0
	DESCRIPTION "Collection of C++ libraries and tools by me"
	LANGUAGES CXX)

include(FetchContent)
include(utils/cmake/CompilerSettings.cmake)
include(utils/cmake/Linters.cmake)

add_subdirectory(libs)
add_subdirectory(apps)
