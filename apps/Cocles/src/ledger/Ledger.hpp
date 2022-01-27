// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_LEDGER_LEDGER_HPP
#define TYBL_COCLES_LEDGER_LEDGER_HPP

#include <memory>
#include <string>
#include <vector>

namespace ledger {

struct Account;
struct Payee;
struct Transaction;

struct Ledger {

  Ledger();

  void insert(Account const& a);

  void insert(Payee const& p);

  void insert(Transaction const& t);

  // Copies all account names that match a specific regex
  [[nodiscard]] std::vector<Account> accounts(std::string const& re) const;

  // Copies all payee names that match a specific regex
  [[nodiscard]] std::vector<Payee> payees(std::string const& re) const;

private:
  struct Impl;
  std::shared_ptr<Impl> m_pimpl;
}; // struct Ledger

std::istream& operator>>(std::istream& s, Ledger& l);

} // namespace ledger

#endif // TYBL_COCLES_LEDGER_LEDGER_HPP
