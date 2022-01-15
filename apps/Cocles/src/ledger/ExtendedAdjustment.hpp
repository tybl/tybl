// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_LEDGER_EXTENDEDADJUSTMENT_HPP
#define TYBL_COCLES_LEDGER_EXTENDEDADJUSTMENT_HPP

#include "Account.hpp"
#include "Payee.hpp"
#include "util/Date.hpp"
#include "util/Money.hpp"

namespace ledger {

struct ExtendedAdjustment {

   ExtendedAdjustment(util::Date date, Payee payee, Account account, util::Money amount);

   [[nodiscard]] util::Date const& date() const;

   [[nodiscard]] Payee const& payee() const;

   [[nodiscard]] Account const& account() const;

   [[nodiscard]] util::Money const& amount() const;

private:
   util::Date  m_date;
   Payee       m_payee;
   Account     m_account;
   util::Money m_amount;
}; // struct ExtendedAdjustment

} // namespace ledger

#endif // TYBL_COCLES_LEDGER_EXTENDEDADJUSTMENT_HPP