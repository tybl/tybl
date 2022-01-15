// License: The Unlicense (https://unlicense.org)
#include "nmea/parse_error.hpp"

namespace nmea {

// TODO(tybl): Two string copies is unnecessary
parse_error::parse_error(std::string p_msg) : message(p_msg) {}

parse_error::parse_error(std::string p_msg, sentence /*n*/) : message(p_msg)/*, nmea(n)*/ {}

parse_error::~parse_error() = default;

// TODO(tybl): Should this return `std::string const&`
std::string parse_error::what() { return message; }

} // namespace nmea
