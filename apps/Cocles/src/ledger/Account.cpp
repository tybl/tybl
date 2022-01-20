// License: The Unlicense (https://unlicense.org)
#include "Account.hpp"

namespace ledger {

Account::Account(std::string name)
  : m_name(std::move(name)) {}

std::string const& Account::name() const { return m_name; }

bool Account::operator<(Account const& other) const { return m_name < other.m_name; }

bool Account::operator==(Account const& other) const { return m_name == other.m_name; }

} // namespace ledger
