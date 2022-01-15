################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(lynel INTERFACE)
target_include_directories(lynel INTERFACE include)
target_link_libraries(lynel INTERFACE compiler_settings)
target_sources(lynel
  INTERFACE
    include/lynel/basic_matrix.hpp
    include/lynel/matrix.hpp
    include/lynel/quaternion.hpp
)

add_subdirectory(test)
