// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_LEDGERIMPL_HPP
#define COCLES_LEDGER_INTERNAL_LEDGERIMPL_HPP

#include "account.hpp"
#include "adjustment.hpp"
#include "transaction.hpp"

#include <algorithm>
#include <memory>
#include <vector>

namespace ledger {

namespace internal {

struct ledger_impl_t {

  account_t* get_account_ptr(std::string account_name) {
    auto account_iter = std::lower_bound(
        accounts.begin(), accounts.end(), account_name,
        [](const std::unique_ptr<account_t>& account, const std::string& str) { return account->name < str; });
    return (accounts.end() == account_iter) ? nullptr : account_iter->get();
  }

  std::vector<std::unique_ptr<account_t>> accounts;
  std::vector<std::unique_ptr<adjustment_t>> adjustments;
  std::vector<std::unique_ptr<transaction_t>> transactions;
}; // struct ledger_impl_t

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_LEDGERIMPL_HPP
