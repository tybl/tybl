################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

find_package(SFML 2.5 COMPONENTS graphics QUIET)
if(SFML_FOUND)

  add_executable(sfml_goon)
  target_include_directories(sfml_goon PUBLIC src)
  target_link_libraries(sfml_goon PRIVATE sfml-graphics)
  target_sources(sfml_goon
    PRIVATE
      src/sfml_main.cpp
  )

else()
  message("Note: Not building \"SFML Goon\"; install SFML to enable")
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
  message("Note: Not building \"SDL2 Goon\"; install SDL2 to enable")
endif()
