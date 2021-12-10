################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

find_package(SFML 2.5 COMPONENTS graphics audio QUIET)
if(SFML_FOUND)

  add_executable(sfml_goon)
  target_include_directories(sfml_goon PUBLIC src)
  target_link_libraries(sfml_goon PRIVATE sfml-graphics)
  target_sources(sfml_goon
    PRIVATE
      src/sfml_main.cpp
  )

else()
endif()

find_package(SDL2 QUIET)
if(SDL2_FOUND)

  add_executable(sdl2_goon)
  target_include_directories(sdl2_goon PUBLIC src)
  target_link_libraries(sdl2_goon SDL2)
  target_sources(sdl2_goon
    PRIVATE
      src/Dispatcher.cpp
      src/Widget.cpp
      src/Window.cpp
      src/main.cpp
  )

else()
  message(STATUS "Goon requires SDL2")
  message(WARNING "Install SDL2")
endif()
