################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(log)
target_include_directories(log PUBLIC include)
target_link_libraries(log
  PUBLIC
    compiler_settings
)
target_sources(log
  PRIVATE
    src/log/logger.cpp
  PUBLIC
    include/log/logger.hpp
)
