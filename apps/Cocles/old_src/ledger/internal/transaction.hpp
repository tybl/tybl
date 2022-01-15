// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_TRANSACTION_HPP
#define COCLES_LEDGER_INTERNAL_TRANSACTION_HPP

#include "ledger/transaction.hpp"

#include "date/date.h"
#include <string>
#include <vector>

namespace ledger {
   namespace internal {
      struct adjustment_t;

      struct transaction_t {
         explicit transaction_t(const ::ledger::transaction_t& trans)
            : memo(trans.memo),
            date(trans.date),
            adjustments()
         {
         }
         std::string memo;
         date::year_month_day date;
         std::vector<adjustment_t*> adjustments;
      }; // transaction_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_TRANSACTION_HPP
