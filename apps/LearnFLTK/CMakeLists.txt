################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13) # relative path target_sources()

find_package(FLTK QUIET)
if(FLTK_FOUND)
  
  find_package(OpenGL REQUIRED)
  
  add_executable(hello)
  target_compile_options(hello PRIVATE -Wall -Wextra -Wpedantic)
  target_link_libraries(hello PRIVATE fltk)
  target_sources(hello
    PRIVATE
      src/hello_world.cpp
  )
  
  add_executable(buttons)
  target_compile_options(buttons PRIVATE -Wall -Wextra -Wpedantic)
  target_link_libraries(buttons PRIVATE fltk)
  target_sources(buttons
    PRIVATE
      src/buttons.cpp
  )
  
  add_executable(progress_bar)
  target_compile_options(progress_bar PRIVATE -Wall -Wextra -Wpedantic)
  target_link_libraries(progress_bar PRIVATE fltk)
  target_sources(progress_bar
    PRIVATE
      src/progress_bar.cpp
  )
  
  
  add_executable(mouse_coord)
  target_compile_options(mouse_coord PRIVATE -Wall -Wextra -Wpedantic)
  target_link_libraries(mouse_coord PRIVATE fltk)
  target_sources(mouse_coord
    PRIVATE
      src/mouse_coord.cpp
  )
  
  add_executable(calculator)
  target_compile_options(calculator PRIVATE -Wall -Wextra -Wpedantic)
  target_link_libraries(calculator PRIVATE fltk)
  target_sources(calculator
    PRIVATE
      src/calculator.cpp
  )
  
  add_executable(glinput)
  target_compile_options(glinput PRIVATE -Wall -Wextra -Wpedantic)
  target_link_libraries(glinput PRIVATE fltk fltk_gl OpenGL::GL OpenGL::GLU)
  target_sources(glinput
    PRIVATE
      src/glinput.cpp
  )
  
else()
  message("Note: FLTK not found; cannot build LearnFLTK")
  message("Install FLTK if you want to build LearnFLTK")
endif()
