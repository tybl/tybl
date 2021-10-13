################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13) # relative path target_sources()

add_executable(stacksolve)
target_compile_features(stacksolve PRIVATE cxx_std_20) # 20: std::set::emplace()
target_compile_options(stacksolve PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(stacksolve PRIVATE src)
target_sources(stacksolve
  PRIVATE
    src/main.cpp
    src/Executor.cpp
    src/Board.cpp
)
