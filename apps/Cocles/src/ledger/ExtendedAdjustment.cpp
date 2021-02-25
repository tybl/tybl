// License: The Unlicense (https://unlicense.org)
#include "ExtendedAdjustment.hpp"

namespace ledger {

// enum class AdjustmentStatus { UNKNOWN, PENDING, CLEARED, RECONCILED };

ExtendedAdjustment::ExtendedAdjustment(util::Date date, Payee payee, Account account, util::Money amount)
   : m_date(date)
   , m_payee(std::move(payee))
   , m_account(std::move(account))
   , m_amount(amount)
{ }

util::Date const& ExtendedAdjustment::date() const { return m_date; }

Payee const& ExtendedAdjustment::payee() const { return m_payee; }

Account const& ExtendedAdjustment::account() const { return m_account; }

util::Money const& ExtendedAdjustment::amount() const { return m_amount; }

} // namespace ledger
