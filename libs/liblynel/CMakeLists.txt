################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

add_library(lynel INTERFACE)
target_include_directories(lynel INTERFACE include)
target_link_libraries(lynel INTERFACE compiler_settings)
target_sources(lynel
  PUBLIC
    include/lynel/basic_matrix.hpp
    include/lynel/matrix.hpp
    include/lynel/quaternion.hpp
)

add_subdirectory(test)
