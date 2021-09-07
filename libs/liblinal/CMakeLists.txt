################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

add_library(linal)
target_include_directories(linal PUBLIC include)
target_link_libraries(linal INTERFACE compiler_settings)
target_sources(linal
  PUBLIC
    include/linal/vec.hpp
    include/linal/vector.hpp
    include/linal/vector_ops.hpp
    include/linal/matrix.hpp
    include/linal/quaternion.hpp
    include/linal/vec3d.hpp
  PRIVATE
    src/linal/vec3d.cpp
)

add_subdirectory(test)
