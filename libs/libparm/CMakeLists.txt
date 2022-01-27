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

#[[
add_executable(libparm_t)
target_link_libraries(libparm_t
  PRIVATE
    compiler_settings
    parm
    test_base
)
target_sources(libparm_t
  PRIVATE
    src/test_help.cpp
)

add_test(NAME test_libparm COMMAND libparm_t)
]]