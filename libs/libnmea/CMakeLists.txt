################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

add_library(nmea)
target_include_directories(nmea PUBLIC include)
target_link_libraries(nmea PUBLIC compiler_settings)
target_sources(nmea
  PRIVATE
    src/gps/Almanac.cpp
    src/gps/Satellite.cpp
    src/gps/Timestamp.cpp
    src/gps/Fix.cpp
    src/nmea/Command.cpp
    src/nmea/GPSService.cpp
    src/nmea/NumberConversion.cpp
    src/nmea/ParseError.cpp
    src/nmea/Parser.cpp
    src/nmea/QueryRate.cpp
    src/nmea/Sentence.cpp
    src/nmea/SerialConfiguration.cpp
  PUBLIC
    include/gps/Almanac.hpp
    include/gps/Satellite.hpp
    include/gps/Timestamp.hpp
    include/gps/Fix.hpp
    include/nmea/Event.hpp
    include/nmea/EventHandler.hpp
    include/nmea/nmea.hpp
    include/nmea/ParseError.hpp
    include/nmea/Parser.hpp
    include/nmea/Sentence.hpp
)

# TODO(tybl): Create tests
#add_subdirectory(test)
