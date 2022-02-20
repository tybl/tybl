################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(nmea)
target_include_directories(nmea PUBLIC include)
target_link_libraries(nmea PUBLIC compiler_settings fmt spdlog vodka)
target_sources(nmea
  PRIVATE
    src/nmea/gps/almanac.cpp
    src/nmea/gps/satellite.cpp
    src/nmea/gps/timestamp.cpp
    src/nmea/gps/fix.cpp
    src/nmea/byte_parser.cpp
    src/nmea/Command.cpp
    src/nmea/GPSService.cpp
    src/nmea/Parser.cpp
    src/nmea/query_rate.cpp
    src/nmea/sentence.cpp
    src/nmea/serial_configuration.cpp
  PUBLIC
    include/nmea/gps/almanac.hpp
    include/nmea/gps/satellite.hpp
    include/nmea/gps/timestamp.hpp
    include/nmea/gps/fix.hpp
    include/nmea/byte_parser.hpp
    include/nmea/Event.hpp
    include/nmea/EventHandler.hpp
    include/nmea/nmea.hpp
    include/nmea/Parser.hpp
    include/nmea/sentence.hpp
)

add_executable(test_libnmea)
target_link_libraries(test_libnmea PRIVATE compiler_settings fmt nmea test_base)
target_sources(test_libnmea
  PRIVATE
    test/nmea/GGA_sentence.cpp
    test/nmea/simple_test.cpp
)

add_test(NAME libnmea_test COMMAND test_libnmea)
