#pragma once

#include "Sentence.hpp"

#include <exception>
#include <string>

namespace nmea {

struct ParseError
  : public std::exception
{
  std::string message;
  Sentence nmea;
public:

  ParseError(std::string msg);

  ParseError(std::string msg, Sentence n);

  virtual ~ParseError();

  // TODO(tybl): Should this `override` std::exception::what()?
  std::string what();

}; // struct ParseError

} // namespace nmea
