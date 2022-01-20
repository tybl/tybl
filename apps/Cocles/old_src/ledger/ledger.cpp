// License: The Unlicense (https://unlicense.org)
#include "ledger.hpp"

#include "account.hpp"
#include "internal/ledger_impl.hpp"
#include "transaction.hpp"

namespace ledger {
ledger_t::ledger_t()
  : impl(std::make_unique<internal::ledger_impl_t>()) {}

ledger_t::ledger_t(ledger_t&&) noexcept = default;

ledger_t::~ledger_t() = default;

ledger_t& ledger_t::operator=(ledger_t&&) noexcept = default;

money_t ledger_t::get_account_balance(std::string account_name) const {
  money_t result("0");
  if (impl) {
    const auto& adjustments = impl->adjustments;
    // find account object
    auto account_ptr = impl->get_account_ptr(account_name);
    // sum adjustment amounts for adjustments pointing to account
    if (nullptr != account_ptr) {
      for (auto& adjust_ptr : adjustments) {
        if (adjust_ptr && adjust_ptr->account_ptr == account_ptr) {
          result += adjust_ptr->amount;
        }
      }
    }
  }
  return result;
}

ledger_t& ledger_t::operator+=(const account_t& account) {
  impl->accounts.emplace_back(std::make_unique<internal::account_t>(account.name, internal::EQUITY));
  return *this;
}

ledger_t& ledger_t::operator+=(const transaction_t& transaction) {
  impl->transactions.emplace_back(std::make_unique<internal::transaction_t>(transaction));
  // internal::transaction_t& new_transaction = *impl->transactions.back().get();
  for (auto adjust : transaction.adjustments) {
    auto account_ptr = impl->get_account_ptr(adjust.account.name);
    if (nullptr == account_ptr) {
      impl->accounts.emplace_back(std::make_unique<internal::account_t>(adjust.account.name, internal::EQUITY));
      account_ptr = impl->accounts.back().get();
    }
    impl->adjustments.emplace_back(std::make_unique<internal::adjustment_t>());
    impl->adjustments.back()->amount = adjust.amount;
    impl->adjustments.back()->account_ptr = account_ptr;
    impl->adjustments.back()->transaction_ptr = impl->transactions.back().get();
  }
  return *this;
}

} // namespace ledger

// Test cases
#include "doctest/doctest.h"

TEST_CASE("ledger_t::get_account_balance") {
  ledger::ledger_t ledger;
  CHECK(ledger::money_t("0") == ledger.get_account_balance("Credit Card"));
}

TEST_CASE("ledger_t::insert_account") {
  ledger::ledger_t ledger;
  ledger::account_t a;
  a.name = "Credit Card";
  ledger += a;
  CHECK(ledger::money_t("0") == ledger.get_account_balance("Credit Card"));
}

TEST_CASE("ledger_t::insert_transaction") {
  ledger::ledger_t ledger;
  ledger::transaction_t trans;
  trans.date = date::year(2016) / 10 / 2;
  trans.memo = "Test";
  ledger::adjustment_t adjust;
  adjust.account.name = "Credit Card";
  adjust.amount = ledger::money_t("500");
  trans.adjustments.push_back(adjust);
  ledger += trans;
  CHECK(ledger.get_account_balance("Credit Card") == ledger::money_t("500"));
}
