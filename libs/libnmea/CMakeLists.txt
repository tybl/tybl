################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(nmea)
target_include_directories(nmea PUBLIC include)
target_link_libraries(nmea PUBLIC compiler_settings fmt spdlog vodka)
target_sources(nmea
  PRIVATE
    src/nmea/byte_parser.cpp
    src/nmea/command.cpp
    src/nmea/gps/almanac.cpp
    src/nmea/gps/fix.cpp
    src/nmea/gps/satellite.cpp
    src/nmea/gps/timestamp.cpp
    src/nmea/gps_service.cpp
    src/nmea/query_rate.cpp
    src/nmea/sentence.cpp
    src/nmea/sentence_parser.cpp
    src/nmea/serial_configuration.cpp
  PUBLIC
    include/nmea/byte_parser.hpp
    include/nmea/command.hpp
    include/nmea/event.hpp
    include/nmea/event_handler.hpp
    include/nmea/gps/almanac.hpp
    include/nmea/gps/fix.hpp
    include/nmea/gps/satellite.hpp
    include/nmea/gps/timestamp.hpp
    include/nmea/gps_service.hpp
    include/nmea/nmea.hpp
    include/nmea/sentence.hpp
    include/nmea/sentence_parser.hpp
)

add_executable(test_libnmea)
target_link_libraries(test_libnmea PRIVATE compiler_settings fmt nmea test_base)
target_sources(test_libnmea
  PRIVATE
    test/nmea/gga_sentence.cpp
    test/nmea/simple_test.cpp
)

add_test(NAME libnmea_test COMMAND test_libnmea)

# libfuzzer requires Clang
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  set(FUZZ_TIMEOUT 10 CACHE STRING "Maximum time, in seconds, to run fuzz test")

  add_executable(fuzz_libnmea)
  target_compile_options(fuzz_libnmea PRIVATE -fsanitize=fuzzer,undefined,address)
  target_link_libraries(fuzz_libnmea PRIVATE compiler_settings nmea -coverage -fsanitize=fuzzer,undefined,address)
  target_sources(fuzz_libnmea PRIVATE test/nmea/fuzz_test.cpp)
  add_test(NAME libnmea_fuzz_test COMMAND fuzz_libnmea -max_total_time=${FUZZ_TIMEOUT})
endif()
