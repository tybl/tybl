cmake_minimum_required(VERSION 3.14)

find_package(SFML COMPONENTS graphics QUIET)

if(SFML_FOUND)

  add_executable(sfml-app)
  target_link_libraries(sfml-app PRIVATE sfml-graphics)
  target_sources(sfml-app PRIVATE src/main.cpp)

else()
  message("Note: SFML not found; cannot build SFML.")
  message("Install SFML if you want to build SFML.")
endif()
