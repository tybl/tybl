// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_ADJUSTMENT_HPP
#define COCLES_LEDGER_ADJUSTMENT_HPP

#include "account.hpp"
#include "money.hpp"

namespace ledger {
struct adjustment_t {
  money_t amount;
  account_t account;
}; // struct adjustment_t
} // namespace ledger
#endif // COCLES_LEDGER_ADJUSTMENT_HPP
