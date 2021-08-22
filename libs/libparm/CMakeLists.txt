################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14)

add_library(parm INTERFACE)
target_include_directories(parm INTERFACE include)
target_sources(parm
  INTERFACE
    include/parm/Application.hpp
    include/parm/Parameter.hpp)

add_subdirectory(test)
