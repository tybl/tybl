################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13) # relative path target_sources()

add_executable(dcp001)
target_compile_features(dcp001 PRIVATE cxx_std_20)
target_compile_options(dcp001 PRIVATE -Wall -Wextra -Wpedantic)
target_sources(dcp001 PRIVATE src/dcp001.cpp)
