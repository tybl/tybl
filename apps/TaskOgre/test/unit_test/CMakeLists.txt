################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

# Define unittests executable target
add_executable(unit_test)
if(CLANG_TIDY_EXE)
  set_target_properties(unit_test PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND_LINE}")
endif()
if(CPPCHECK_EXE)
  set_target_properties(unit_test PROPERTIES CXX_CPPCHECK "${CPPCHECK_COMMAND_LINE}")
endif()
target_link_libraries(unit_test
  PRIVATE
    compile_settings
    doctest::doctest
    tasklib)
target_sources(unit_test
  PRIVATE
    tasklib/cli/Command.cpp
    main.cpp)
add_test(NAME unit_test_t COMMAND unit_test)
