################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.18)

project(tybl
	VERSION 0.0.0
	DESCRIPTION "Collection of C++ libraries, applications and tools written by me"
	LANGUAGES CXX)

find_package(date REQUIRED)
find_package(doctest REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

include(CTest)
include(utils/cmake/CompilerSettings.cmake)
include(utils/cmake/Linters.cmake)

add_subdirectory(utils/doctest)
add_subdirectory(libs)
add_subdirectory(apps)
