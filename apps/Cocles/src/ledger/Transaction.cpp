// License: The Unlicense (https://unlicense.org)
#include "Transaction.hpp"

#include "transaction/Builder.hpp"

namespace ledger {

Transaction::Transaction(Transaction::Builder const& b)
  : m_date(b.date())
  , m_payee(b.payee())
  , m_adjustments(b.adjustments()) {}

std::vector<Adjustment> const& Transaction::adjustments() const { return m_adjustments; }

util::Date const& Transaction::date() const { return m_date; }

Payee const& Transaction::payee() const { return m_payee; }

} // namespace ledger
