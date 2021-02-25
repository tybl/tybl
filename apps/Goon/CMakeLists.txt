################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

# Describe the project
project(goon
	VERSION 0.0.1
	DESCRIPTION "Astroids clone"
	LANGUAGES CXX)

# Prepare useful modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/tools/cmake" ${CMAKE_MODULE_PATH})
include(SetTargetMaxCompileWarnings)

# Find and apply useful executables
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
	message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
	set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
endif()
find_program(CPPCHECK_EXE NAMES cppcheck)
if(CPPCHECK_EXE)
	message(STATUS "cppcheck found: ${CPPCHECK_EXE}")
	set(CMAKE_CXX_CPPCHECK ${CPPCHECK_EXE})
endif()
find_program(INCLUDE_WHAT_YOU_USE_EXE NAMES include-what-you-use)
if(INCLUDE_WHAT_YOU_USE_EXE)
	message(STATUS "include-what-you-use found: ${INCLUDE_WHAT_YOU_USE_EXE}")
	set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${INCLUDE_WHAT_YOU_USE_EXE};-Xiwyu;--mapping_file=${PROJECT_SOURCE_DIR}/tools/include-what-you-use_mapping-file.imp;-Xiwyu;--quoted_includes_first;-Xiwyu;--cxx17ns;-Xiwyu;--max_line_length=120")
endif()

# Describe executable
add_executable(goon)
target_sources(goon
	PRIVATE
		src/Dispatcher.cpp
		src/Widget.cpp
		src/Window.cpp
		src/main.cpp)
target_include_directories(goon PUBLIC src)
target_link_libraries(goon SDL2)
set_target_properties(goon PROPERTIES
	CXX_STANDARD 20
	CXX_EXTENSIONS NO)
set_target_max_compile_warnings(goon)
