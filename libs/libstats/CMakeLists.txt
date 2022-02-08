################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

find_package(Eigen3 3.3 QUIET NO_MODULE)

if(Eigen3_FOUND)

  add_library(stats INTERFACE)
  target_include_directories(stats INTERFACE include)
  target_link_libraries(stats INTERFACE Eigen3::Eigen)
  target_sources(stats INTERFACE include/stats/distribution.hpp)

  add_executable(test_libstats)
  target_link_libraries(test_libstats
    PRIVATE
      doctest::doctest
      stats
  )
  target_sources(test_libstats
    PRIVATE
      test/stats/main.cpp
  )
  add_test(NAME libstats_test COMMAND test_libstats)

else()
  message("Note: Not building \"libstats\"; install Eigen3 to enable")
endif()
