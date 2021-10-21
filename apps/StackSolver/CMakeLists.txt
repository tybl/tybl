################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13) # relative path target_sources()

message(${CMAKE_CXX_COMPILER_VERSION})
if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "10.1")

add_executable(find_all)
target_compile_features(find_all PUBLIC cxx_std_20) # 20: std::set::emplace(), std::ranges
target_sources(find_all
  PRIVATE
    src/find_all.cpp
)

add_library(stacksolvelib)
target_compile_features(stacksolvelib PUBLIC cxx_std_20) # 20: std::set::emplace()
target_compile_options(stacksolvelib PUBLIC -Wall -Wextra -Wpedantic)
target_include_directories(stacksolvelib PUBLIC src)
target_sources(stacksolvelib
  PRIVATE
    src/Executor.cpp
    src/Board.cpp
)

add_executable(stacksolve)
target_link_libraries(stacksolve PRIVATE stacksolvelib)
target_sources(stacksolve PRIVATE src/main.cpp)

add_subdirectory(test)

else()
  message(STATUS "StackSolver requires std::range")
  message(WARNING "Install gcc 10.1 or greater")
endif()
