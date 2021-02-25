// License: The Unlicense (https://unlicense.org)
#include "Adjustment.hpp"

namespace ledger {

// enum class AdjustmentStatus { UNKNOWN, PENDING, CLEARED, RECONCILED };

Adjustment::Adjustment(Account account, util::Money amount)
   : m_account(std::move(account))
   , m_amount(amount)
{ }

Account const& Adjustment::account() const { return m_account; }

util::Money const& Adjustment::amount() const { return m_amount; }

} // namespace ledger
