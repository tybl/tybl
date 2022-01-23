// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_PARSEERROR_HPP
#define TYBL_VODKA_PARSEERROR_HPP

#include <stdexcept>

namespace tybl::vodka {

struct parse_error
  : public std::runtime_error
{
  using std::runtime_error::runtime_error;
}; // struct parse_error

} // namespace tybl::vodka

#endif // TYBL_VODKA_PARSEERROR_HPP