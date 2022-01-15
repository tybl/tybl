################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(math INTERFACE)
target_include_directories(math INTERFACE include)
target_link_libraries(math INTERFACE compiler_settings)
target_sources(math
  INTERFACE
    include/math/stats/distribution.hpp
    include/math/stats/probability.hpp
    include/math/pow10.hpp
)

add_subdirectory(test)
