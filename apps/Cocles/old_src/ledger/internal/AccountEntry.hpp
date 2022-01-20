// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_ACCOUNTENTRY_HPP
#define COCLES_LEDGER_INTERNAL_ACCOUNTENTRY_HPP

#include "EntryProxy.hpp"

#include "AccountTypeEntry.hpp"

#include <string>

struct Account {
  std::string name;
  AccountTypeEntry type;
};

using AccountEntry = ledger::internal::EntryProxy<Account>;

#endif // COCLES_LEDGER_INTERNAL_ACCOUNTENTRY_HPP
