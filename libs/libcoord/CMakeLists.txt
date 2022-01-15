################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(coord)
target_include_directories(coord PUBLIC include)
target_link_libraries(coord
  PUBLIC
    lynel
    vodka
)
target_sources(coord
  PRIVATE
    src/coord/ecef.cpp
    src/coord/enu.cpp
    src/coord/frd.cpp
    src/coord/lla.cpp
    src/coord/ned.cpp
    src/coord/rae.cpp
  PUBLIC
    include/coord/ecef.hpp
    include/coord/enu.hpp
    include/coord/frd.hpp
    include/coord/lla.hpp
    include/coord/ned.hpp
    include/coord/rae.hpp
)

add_subdirectory(test)
