################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

add_library(nmea)
target_include_directories(nmea PUBLIC include)
target_link_libraries(nmea PUBLIC compiler_settings)
target_sources(nmea
  PRIVATE
        src/gps/almanac.cpp
        src/gps/satellite.cpp
        src/gps/timestamp.cpp
        src/gps/fix.cpp
    src/nmea/Command.cpp
    src/nmea/GPSService.cpp
        src/nmea/parse_error.cpp
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
        include/nmea/parse_error.hpp
    include/nmea/Parser.hpp
        include/nmea/sentence.hpp
)

add_subdirectory(test)
