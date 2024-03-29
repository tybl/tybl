// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_LEDGER_PARSE_ADJUSTMENT_HPP
#define TYBL_COCLES_LEDGER_PARSE_ADJUSTMENT_HPP

#include "util/Money.hpp"

#include <string>

struct adjustment_t {

  explicit adjustment_t(std::string input)
    : m_value(std::move(input)) {}

private:
  std::string m_value;
  std::string m_account;
  util::Money m_amount;
}; // struct adjustment_t

#endif // TYBL_COCLES_LEDGER_PARSE_ADJUSTMENT_HPP
