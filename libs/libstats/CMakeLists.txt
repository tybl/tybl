################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

find_package(Eigen3 3.3 QUIET NO_MODULE)

if(Eigen3_FOUND)

add_library(stats INTERFACE)
target_include_directories(stats INTERFACE include)
target_link_libraries(stats INTERFACE Eigen3::Eigen)
target_sources(stats INTERFACE include/stats/distribution.hpp)

add_subdirectory(test)

else()
  message(WARNING "Not building libstats, install Eigen3")
endif()
