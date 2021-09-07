################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

add_library(lynel)
target_include_directories(lynel PUBLIC include)
target_link_libraries(lynel INTERFACE compiler_settings)
target_sources(lynel
  PUBLIC
    include/lynel/vec.hpp
    include/lynel/vector.hpp
    include/lynel/vector_ops.hpp
    include/lynel/matrix.hpp
    include/lynel/quaternion.hpp
    include/lynel/vec3d.hpp
  PRIVATE
    src/lynel/vec3d.cpp
)

add_subdirectory(test)
