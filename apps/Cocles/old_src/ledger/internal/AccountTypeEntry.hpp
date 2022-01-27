// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_ACCOUNTTYPEENTRY_HPP
#define COCLES_LEDGER_INTERNAL_ACCOUNTTYPEENTRY_HPP

#include "EntryProxy.hpp"

#include <string>

struct AccountType {
  std::string name;
};

using AccountTypeEntry = ledger::internal::EntryProxy<AccountType>;

#endif // COCLES_LEDGER_INTERNAL_ACCOUNTTYPEENTRY_HPP
