#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <exception>


namespace nmea {

class NumberConversionError : public std::exception {
public:
  std::string message;
  NumberConversionError(std::string msg)
    : message(msg)
  {};

  virtual ~NumberConversionError()
  {};

  std::string what(){
    return message;
  }
};

double parseDouble(std::string s);
int64_t parseInt(std::string s, int radix = 10);

//void NumberConversion_test();

} // namespace nmea
