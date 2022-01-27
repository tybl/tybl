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

#[[
# TODO: Create unit tests
add_executable(libcoord_t)
target_link_libraries(libcoord_t PRIVATE compiler_settings test_base)
target_sources(libcoord_t
  PRIVATE
)
add_test(NAME test_libcoord COMMAND libcoord_t)
]]
