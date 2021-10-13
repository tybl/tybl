################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13) # relative path target_sources()

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
