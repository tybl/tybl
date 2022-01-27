################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

find_package(SFML COMPONENTS graphics QUIET)

if(SFML_FOUND)

  add_executable(sfml-app)
  target_link_libraries(sfml-app PRIVATE sfml-graphics)
  target_sources(sfml-app PRIVATE src/main.cpp)

else()
  message("Note: Not building \"SFML\"; install SFML to enable")
endif()
