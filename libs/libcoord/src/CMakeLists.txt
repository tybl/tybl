################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(example)
target_link_libraries(example PRIVATE compiler_settings)
target_sources(example PRIVATE example/main.cpp)

add_library(coord)
target_link_libraries(coord
  PRIVATE
    eigen
    units)
target_sources(coord
  PRIVATE
    coord/ecef.cpp
    coord/enu.cpp
    coord/frd.cpp
    coord/lla.cpp
    coord/ned.cpp
    coord/rae.cpp
  PUBLIC
    coord/ecef.hpp
    coord/enu.hpp
    coord/frd.hpp
    coord/lla.hpp
    coord/ned.hpp
    coord/rae.hpp)
