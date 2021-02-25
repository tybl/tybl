################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

# libfuzzer requires Clang
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  add_subdirectory(fuzz_test)
endif()
add_subdirectory(unit_test)
