################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

find_package(SDL2 QUIET)
if(SDL2_FOUND)

  add_executable(goon)
  target_include_directories(goon PUBLIC src)
  target_link_libraries(goon SDL2)
  target_sources(goon
    PRIVATE
      src/Dispatcher.cpp
      src/Widget.cpp
      src/Window.cpp
      src/main.cpp
  )

else()
  message("Note: SDL2 not found; cannot build Goon.")
  message("Install SDL2 if you want to build Goon.")
endif()
