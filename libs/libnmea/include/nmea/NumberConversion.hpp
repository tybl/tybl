#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <exception>


namespace nmea {

double parseDouble(std::string s);
int64_t parseInt(std::string s, int radix = 10);

//void NumberConversion_test();

} // namespace nmea
