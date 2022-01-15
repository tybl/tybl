// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_ADJUSTMENT_HPP
#define COCLES_LEDGER_INTERNAL_ADJUSTMENT_HPP

#include "ledger/money.hpp"

namespace ledger {
   namespace internal {
      struct account_t;
      struct transaction_t;
      struct adjustment_t {
         transaction_t* transaction_ptr;
         account_t* account_ptr;
         money_t amount;
      }; // struct adjustment_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_ADJUSTMENT_HPP
