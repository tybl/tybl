// License: The Unlicense (https://unlicense.org)
#ifndef COCLES_LEDGER_INTERNAL_ACCOUNT_HPP
#define COCLES_LEDGER_INTERNAL_ACCOUNT_HPP

#include <string>

namespace ledger {
   namespace internal {
      enum account_type_t {
         EQUITY,
         INCOME_EXPENSE,
         ASSET_LIABILITY,
         BUDGET_CATEGORY
      };
      struct account_t {
         account_t(std::string p_name, account_type_t p_type);
         std::string name;
         std::string memo;
         account_type_t type;
      }; // struct account_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_ACCOUNT_HPP
