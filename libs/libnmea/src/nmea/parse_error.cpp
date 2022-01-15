#include "nmea/parse_error.hpp"

namespace nmea {

// TODO(tybl): Two string copies is unnecessary
parse_error::parse_error(std::string msg) : message(msg) {}

parse_error::parse_error(std::string msg, sentence /*n*/) : message(msg)/*, nmea(n)*/ {}

parse_error::~parse_error() = default;

// TODO(tybl): Should this return `std::string const&`
std::string parse_error::what() { return message; }

} // namespace nmea
