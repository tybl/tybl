################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

project(TaskOgre
  VERSION 0.0.0
  DESCRIPTION "Taskwarrior clone"
  LANGUAGES CXX)

option(BUILD_PROJECT_TESTS "Build and run tests as a subproject" OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()
include(FetchContent)
include(util/cmake/CompilerSettings.cmake)
include(util/cmake/Linters.cmake)

# External Projects
## Test framework
FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "2.4.0")
FetchContent_MakeAvailable(doctest)
## Formatting library
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_SHALLOW    TRUE
  GIT_TAG        "7.0.3")
FetchContent_MakeAvailable(fmt)
## Standard library
FetchContent_Declare(libvodka
  GIT_REPOSITORY https://github.com/tybl/libvodka.git
  GIT_SHALLOW    TRUE
  GIT_TAG        origin/main)
FetchContent_MakeAvailable(libvodka)

add_subdirectory(src)
add_subdirectory(app)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) OR BUILD_PROJECT_TESTS)
  add_subdirectory(test)
endif()
