################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(task)
if(CLANG_TIDY_EXE)
  set_target_properties(task PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND_LINE}")
endif()
if(CPPCHECK_EXE)
  set_target_properties(task PROPERTIES CXX_CPPCHECK "${CPPCHECK_COMMAND_LINE}")
endif()
target_compile_definitions(task
  PRIVATE
    -DPROJECT_NAME="${CMAKE_PROJECT_NAME}"
    -DPROJECT_VERSION="${CMAKE_PROJECT_VERSION}")
target_link_libraries(task PRIVATE compiler_settings tasklib)
target_sources(task
  PRIVATE
    task/main.cpp)
