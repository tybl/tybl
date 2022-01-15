################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(json INTERFACE)
target_include_directories(json INTERFACE include)
#[[
target_link_libraries(json PUBLIC compiler_settings)
target_sources(json
  PUBLIC
    include/json/value.hpp
)
]]

add_subdirectory(test)
