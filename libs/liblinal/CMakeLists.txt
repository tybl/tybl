################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

add_library(linal INTERFACE)
target_include_directories(linal INTERFACE include)
target_link_libraries(linal INTERFACE compiler_settings)
target_sources(linal
  PUBLIC
    include/linal/basic_matrix.hpp
    include/linal/matrix.hpp
    include/linal/quaternion.hpp
)

add_subdirectory(test)
