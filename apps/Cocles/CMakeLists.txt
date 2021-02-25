################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
# Hints: http://www.brianlheim.com/2018/04/09/cmake-cheat-sheet.html
# for clang-tidy: http://mariobadr.com/using-clang-tidy-with-cmake-36.html
cmake_minimum_required(VERSION 3.13)
project(cocles
	VERSION 0.0
	DESCRIPTION "Thanks, Cocles; you are the pearl of cachiers."
	LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(SetTargetMaxCompileWarnings)
#[[
# Define ledger library target
add_library(ledger)
target_compile_features(ledger PUBLIC cxx_std_17)
set_target_properties(ledger PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS NO
	INTERPROCEDURAL_OPTIMIZATION ON
	POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

set(EXEC_NAME cocles)
set(LIB_NAME ledger)
file(GLOB_RECURSE LIB_SOURCES src/ledger/*.cpp src/util/*.cpp)
set(TEST_NAME libledgertest)
file(GLOB_RECURSE TEST_SOURCES test/ledger/*.cpp test/util/*.cpp)

find_package(Boost 1.68 REQUIRED date_time)

include_directories(include src ${Boost_INCLUDE_DIRS})
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})

add_executable(${EXEC_NAME} src/main.cpp)
target_link_libraries(${EXEC_NAME} ${LIB_NAME})
target_link_libraries(${EXEC_NAME} ${Boost_LIBRARIES})

enable_testing()

add_executable(${TEST_NAME} test/main.cpp ${TEST_SOURCES})
target_link_libraries(${TEST_NAME} ${LIB_NAME})
target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES})
add_test(${TEST_NAME} ${TEST_NAME})

# Enable all available warnings
if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
	target_compile_options(${LIB_NAME} PUBLIC -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	target_compile_options(${LIB_NAME} PUBLIC -Wall -Wextra)
else()
	message(SEND_ERROR "Unknown compiler: " ${CMAKE_CXX_COMPILER_ID})
endif()
target_compile_options(${LIB_NAME} PUBLIC -pedantic)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
	message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
	set_target_properties(ledger PROPERTIES CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
endif()

find_program(CPPCHECK_EXE NAMES cppcheck)
if(CPPCHECK_EXE)
	message(STATUS "cppcheck found: ${CPPCHECK_EXE}")
	set_target_properties(ledger PROPERTIES CXX_CPPCHECK ${CPPCHECK_EXE})
endif()
]]
add_executable(cocles apps/cocles.cpp)
set_target_properties(cocles PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS NO)
set_target_max_compile_warnings(cocles)
