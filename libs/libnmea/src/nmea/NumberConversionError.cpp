//
// Created by tybl on 12/31/21.
//

#include "nmea/NumberConversionError.hpp"

namespace nmea {

NumberConversionError::NumberConversionError(std::string msg)
  : m_message(msg)
{ }

NumberConversionError::~NumberConversionError() = default;

std::string NumberConversionError::what() { return m_message; }

} // namespace nmea