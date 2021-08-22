################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13) # relative path target_sources()

add_executable(sort)
target_compile_features(sort PRIVATE cxx_std_20) # 20: std::set::emplace()
target_compile_options(sort PRIVATE -Wall -Wextra -Wpedantic)
target_sources(sort
  PRIVATE
    src/main.cpp
    src/Executor.cpp
    src/Board.cpp
)
