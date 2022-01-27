// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_LEDGER_ACCOUNT_HPP
#define TYBL_COCLES_LEDGER_ACCOUNT_HPP

#include <memory>
#include <string>

namespace ledger {

struct Account {

  explicit Account(std::string name);

  [[nodiscard]] std::string const& name() const;

  [[nodiscard]] bool operator<(Account const& other) const;

  [[nodiscard]] bool operator==(Account const& other) const;

private:
  std::string m_name;
}; // struct Account

} // namespace ledger

#endif // TYBL_COCLES_LEDGER_ACCOUNT_HPP
