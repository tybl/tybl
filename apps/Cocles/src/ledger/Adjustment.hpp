// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_LEDGER_ADJUSTMENT_HPP
#define TYBL_COCLES_LEDGER_ADJUSTMENT_HPP

#include "Account.hpp"
#include "util/Money.hpp"

namespace ledger {

struct Adjustment {

   Adjustment(Account account, util::Money amount);

   [[nodiscard]] Account const& account() const;

   [[nodiscard]] util::Money const& amount() const;

private:
   Account     m_account;
   util::Money m_amount;
}; // struct Adjustment

} // namespace ledger

#endif // TYBL_COCLES_LEDGER_ADJUSTMENT_HPP
