// License: The Unlicense (https://unlicense.org)
///////////////////////////////////////////////////////////////////////////////
// Defines class to represent money
//
// Only represent up to 10,000,000,000,000,000.00
//
// Use cases:
// - Sum up amounts from each adjustment for a specific account
// - Convert to a string for display
///////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef COCLES_LEDGER_MONEY_HPP
#define COCLES_LEDGER_MONEY_HPP

//TODO: which is larger, ostream or iosfwd? Put the smaller here
#include <ostream>
#include <string>
//#include <gmp.h>

namespace ledger {

struct money_t {

   money_t(void);

   explicit money_t(const std::string& new_value);

   money_t(const money_t &other);

   std::string to_string(void) const;

   money_t& operator = (money_t other);

   money_t& operator += (const money_t &other);

   bool operator == (const money_t &other) const;

private:
   //mpz_t value;
   int64_t value;
}; // struct money_t

std::ostream& operator << (std::ostream &out, const money_t &a);

money_t operator + (money_t lhs, const money_t &rhs);

} // namespace ledger

#endif // COCLES_LEDGER_MONEY_HPP
