// License: The Unlicense (https://unlicense.org)
#include "account.hpp"

namespace ledger {
   namespace internal {
      account_t::account_t(std::string p_name, account_type_t p_type)
         : name(std::move(p_name)),
         type(p_type)
      {
      }
   } // namespace internal
} // namespace ledger
