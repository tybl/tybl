// License: The Unlicense (https://unlicense.org)
#ifndef COCLES_LEDGER_PARSE_ADJUSTMENT_HPP
#define COCLES_LEDGER_PARSE_ADJUSTMENT_HPP

#include "util/Money.hpp"

#include <string>

struct adjustment_t {

   explicit adjustment_t(std::string input)
      : m_value(std::move(input))
   {
   }

private:
   std::string m_value;
   std::string m_account;
   util::Money m_amount;
}; // struct adjustment_t

#endif // COCLES_LEDGER_PARSE_ADJUSTMENT_HPP
