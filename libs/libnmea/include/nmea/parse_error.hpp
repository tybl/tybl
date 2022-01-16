// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_PARSEERROR_HPP
#define TYBL_NMEA_PARSEERROR_HPP

#include "sentence.hpp"

#include <exception>
#include <string>

namespace nmea {

struct parse_error
  : public std::exception
{
  std::string message;
//  sentence nmea;
  parse_error(std::string p_msg);

  parse_error(std::string p_msg, sentence p_n);

  virtual ~parse_error();

  // TODO(tybl): Should this `override` std::exception::what()?
  std::string what();

}; // struct parse_error

} // namespace nmea

#endif // TYBL_NMEA_PARSEERROR_HPP
