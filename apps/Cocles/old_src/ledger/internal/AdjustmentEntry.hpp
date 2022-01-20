// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_ADJUSTMENTENTRY_HPP
#define COCLES_LEDGER_INTERNAL_ADJUSTMENTENTRY_HPP

#include "EntryProxy.hpp"

#include "AccountEntry.hpp"
#include "TransactionEntry.hpp"

struct Adjustment {
  AccountEntry account;
  TransactionEntry transaction;
};

using AdjustmentEntry = ledger::internal::EntryProxy<Adjustment>;

#endif // COCLES_LEDGER_INTERNAL_ADJUSTMENTENTRY_HPP
