################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(parm INTERFACE)
target_include_directories(parm INTERFACE include)
target_sources(parm
  INTERFACE
    include/parm/Application.hpp
    include/parm/Parameter.hpp
)

# TODO(tybl): Create unit tests