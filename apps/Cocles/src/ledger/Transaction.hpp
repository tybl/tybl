// License: The Unlicense (https://unlicense.org)
#ifndef COCLES_LEDGER_TRANSACTION_HPP
#define COCLES_LEDGER_TRANSACTION_HPP

#include "Adjustment.hpp"
#include "Payee.hpp"
#include "util/Date.hpp"
#include "util/Money.hpp"

namespace ledger {

struct Transaction {
   struct Builder;

   explicit Transaction(Builder const& b);

   [[nodiscard]] std::vector<Adjustment> const& adjustments() const;

   [[nodiscard]] util::Date const& date() const;

   [[nodiscard]] Payee const& payee() const;

private:
   util::Date m_date;
   Payee      m_payee;
   std::vector<Adjustment> m_adjustments;
}; // struct Transaction


} // namespace ledger

#endif // COCLES_LEDGER_TRANSACTION_HPP
