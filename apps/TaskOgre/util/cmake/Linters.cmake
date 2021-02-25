################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

# TODO: Does it make sense not to enable linters on release builds?
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CLANG_TIDY_EXE clang-tidy-10)
if(CLANG_TIDY_EXE)
  message(STATUS "Found clang-tidy")
  set(CLANG_TIDY_COMMAND_LINE "${CLANG_TIDY_EXE};-p=${CMAKE_BINARY_DIR}")
else()
  message(STATUS "clang-tidy NOT found")
endif()

#find_program(CPPCHECK_EXE cppcheck)
if(CPPCHECK_EXE)
  message(STATUS "Found cppcheck")
  set(CPPCHECK_COMMAND_LINE "${CPPCHECK_EXE};--force")
else()
  message(STATUS "cppcheck NOT found")
endif()

#find_program(IWYU_EXE include-what-you-use)
if(IWYU_EXE)
  message(STATUS "Found include-what-you-use")
  set(CXX_INCLUDE_WHAT_YOU_USE "${IWYU_EXE};-Xiwyu;--quoted_includes_first;-Xiwyu;--cxx17ns;-Xiwyu;--max_line_length=80")
else()
  message(STATUS "include-what-you-use NOT found")
endif()
