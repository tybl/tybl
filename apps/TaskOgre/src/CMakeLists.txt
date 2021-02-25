################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(tasklib)
if(CLANG_TIDY_EXE)
  set_target_properties(tasklib PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND_LINE}")
endif()
if(CPPCHECK_EXE)
  set_target_properties(tasklib PROPERTIES CXX_CPPCHECK "${CPPCHECK_COMMAND_LINE}")
endif()
target_include_directories(tasklib PUBLIC tasklib)
target_link_libraries(tasklib PUBLIC compiler_settings vodka)
target_sources(tasklib
  PRIVATE
    tasklib/cli/Command.cpp
    tasklib/util/uuid.cpp
  PUBLIC
    tasklib/cli/Command.hpp
    tasklib/util/uuid.hpp)
