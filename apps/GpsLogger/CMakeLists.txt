################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

add_executable(gps_logger)
target_link_libraries(gps_logger PRIVATE nmea)
target_sources(gps_logger PRIVATE src/main.cpp)
