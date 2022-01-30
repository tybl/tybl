// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef _TYBL__VODKA__PARSE_ERROR__HPP_
#define _TYBL__VODKA__PARSE_ERROR__HPP_

#include <stdexcept>

namespace tybl::vodka {

struct parse_error : public std::runtime_error {
  using std::runtime_error::runtime_error;
}; // struct parse_error

} // namespace tybl::vodka

#endif // _TYBL__VODKA__PARSE_ERROR__HPP_
