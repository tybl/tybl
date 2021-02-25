################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

set(FUZZ_TIMEOUT 10 CACHE STRING "Maximum time, in seconds, to run fuzz test")

add_executable(fuzz_test main.cpp)
target_compile_options(fuzz_test
  PRIVATE -fsanitize=fuzzer,undefined,address)
target_link_libraries(fuzz_test
  PRIVATE compiler_settings -coverage -fsanitize=fuzzer,undefined,address)
add_test(NAME fuzz_test_t COMMAND fuzz_test -max_total_time=${FUZZ_TIMEOUT})
