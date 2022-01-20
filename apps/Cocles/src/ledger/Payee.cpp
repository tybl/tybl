// License: The Unlicense (https://unlicense.org)
#include "Payee.hpp"

#include <utility>

namespace ledger {

Payee::Payee(std::string name)
  : m_name(std::move(name)) {}

std::string const& Payee::name() const { return m_name; }

bool Payee::operator<(Payee const& other) const { return m_name < other.m_name; }

bool Payee::operator==(Payee const& other) const { return m_name == other.m_name; }

} // namespace ledger
