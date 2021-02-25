// License: The Unlicense (https://unlicense.org)
#ifndef COCLES_LEDGER_EVENT_HPP
#define COCLES_LEDGER_EVENT_HPP

#include "account.hpp"
#include "adjustment.hpp"
#include "transaction.hpp"

#include <chrono>

namespace ledger {
   struct event_t {
      std::chrono::system_clock::time_point timestamp;
      enum { INSERT, MODIFY, REMOVE } event;
      enum { ACCOUNT, ADJUSTMENT, TRANSACTION } type;
      union {
         account_t account;
         adjustment_t adjustment;
         transaction_t transaction;
      };
   };
}
#endif // COCLES_LEDGER_EVENT_HPP
