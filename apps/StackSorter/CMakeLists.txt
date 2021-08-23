################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13) # relative path target_sources()

add_executable(stacksort)
target_compile_features(stacksort PRIVATE cxx_std_20) # 20: std::set::emplace()
target_compile_options(stacksort PRIVATE -Wall -Wextra -Wpedantic)
target_sources(stacksort
  PRIVATE
    src/main.cpp
    src/Executor.cpp
    src/Board.cpp
)
