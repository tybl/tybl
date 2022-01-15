// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_LEDGER_TRANSACTION_BUILDER_HPP
#define TYBL_COCLES_LEDGER_TRANSACTION_BUILDER_HPP

#include "ledger/Transaction.hpp"

namespace ledger {

struct Transaction::Builder {

   Builder& set_date(util::Date date);

   Builder& set_date(std::string const& date);

   Builder& set_payee(Payee payee);

   Builder& set_payee(std::string const& payee);

   Builder& add_adjustment(Adjustment const& adjustment);

   [[nodiscard]] bool is_valid() const;

   [[nodiscard]] util::Date const& date() const;

   [[nodiscard]] Payee const& payee() const;

   [[nodiscard]] std::vector<Adjustment> const& adjustments() const;

   [[nodiscard]] Transaction build() const;

   friend std::istream& operator>>(std::istream& s, Transaction::Builder& t);

private:
   util::Date              m_date;
   Payee                   m_payee;
   std::vector<Adjustment> m_adjustments;
}; // struct Transaction::Builder

} // namespace ledger

#endif // TYBL_COCLES_LEDGER_TRANSACTION_BUILDER_HPP
