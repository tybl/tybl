################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.13)

add_executable(libnmea_t)
target_link_libraries(libnmea_t PRIVATE compiler_settings nmea test_base)
target_sources(libnmea_t
	PRIVATE
	src/GGA_sentence.cpp
	#src/GSA_sentence.cpp
)

add_test(NAME test_libnmea COMMAND libnmea_t)
