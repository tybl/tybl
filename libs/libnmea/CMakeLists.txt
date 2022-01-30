################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(nmea)
target_include_directories(nmea PUBLIC include)
target_link_libraries(nmea PUBLIC compiler_settings vodka)
target_sources(nmea
  PRIVATE
    src/gps/almanac.cpp
    src/gps/satellite.cpp
    src/gps/timestamp.cpp
    src/gps/fix.cpp
    src/nmea/Command.cpp
    src/nmea/GPSService.cpp
    src/nmea/Parser.cpp
    src/nmea/query_rate.cpp
    src/nmea/sentence.cpp
    src/nmea/serial_configuration.cpp
  PUBLIC
    include/gps/almanac.hpp
    include/gps/satellite.hpp
    include/gps/timestamp.hpp
    include/gps/fix.hpp
    include/nmea/Event.hpp
    include/nmea/EventHandler.hpp
    include/nmea/nmea.hpp
    include/nmea/Parser.hpp
    include/nmea/sentence.hpp
)

add_executable(libnmea_t)
target_link_libraries(libnmea_t PRIVATE compiler_settings nmea test_base)
target_sources(libnmea_t
  PRIVATE
    test/nmea/GGA_sentence.cpp
    #test/nmea/GSA_sentence.cpp
)

add_test(NAME test_libnmea COMMAND libnmea_t)
