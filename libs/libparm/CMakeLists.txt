################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(parm)
target_include_directories(parm PUBLIC include)
target_link_libraries(parm PUBLIC compiler_settings vodka)
target_sources(parm
  PUBLIC
    include/parm/Application.hpp
    include/parm/Parameter.hpp
  PRIVATE
    src/parm/Application.cpp
)

# TODO(tybl): Create unit tests
