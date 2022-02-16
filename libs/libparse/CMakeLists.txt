################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(parse INTERFACE)
target_include_directories(parse INTERFACE include)
target_link_libraries(parse INTERFACE compiler_settings)
target_sources(parse
  INTERFACE
    include/parse/character.hpp
)
