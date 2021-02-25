################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

set(FUZZ_TIMEOUT 10 CACHE STRING "Maximum time, in seconds, to run fuzz test")

add_executable(fuzz_test main.cpp)
target_compile_options(fuzz_test
  PRIVATE -fsanitize=fuzzer,undefined,address)
target_link_libraries(fuzz_test
  PRIVATE parm compile_settings -coverage -fsanitize=fuzzer,undefined,address)

add_test(NAME build_fuzz_test_t
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target fuzz_test)
set_tests_properties(build_fuzz_test_t PROPERTIES FIXTURES_SETUP fuzz_test_tf)

add_test(NAME run_fuzz_test_t
  COMMAND fuzz_test -max_total_time=${FUZZ_TIMEOUT})
set_tests_properties(run_fuzz_test_t PROPERTIES FIXTURES_REQUIRED fuzz_test_tf)
