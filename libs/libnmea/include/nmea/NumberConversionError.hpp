// License: The Unlicense (https://unlicense.org)
#pragma once

#include <exception>
#include <string>

namespace nmea {

class NumberConversionError
  : public std::exception
{
  std::string m_message;
public:

  NumberConversionError(std::string msg);

  virtual ~NumberConversionError();

  std::string what();

}; // class NumberConversionError

} // namespace nmea