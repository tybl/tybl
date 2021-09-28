################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13) # relative path target_sources()

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(stats INTERFACE)
target_include_directories(stats INTERFACE include)
target_link_libraries(stats INTERFACE Eigen3::Eigen)
target_sources(stats INTERFACE include/stats/distribution.hpp)

add_subdirectory(test)
