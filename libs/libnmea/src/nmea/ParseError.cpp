#include "nmea/ParseError.hpp"

namespace nmea {

// TODO(tybl): Two string copies is unnecessary
ParseError::ParseError(std::string msg) : message(msg) {}

ParseError::ParseError(std::string msg, Sentence n) : message(msg)/*, nmea(n)*/ {}

ParseError::~ParseError() = default;

// TODO(tybl): Should this return `std::string const&`
std::string ParseError::what() { return message; }

} // namespace nmea
