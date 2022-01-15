// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_LEDGER_HPP
#define COCLES_LEDGER_LEDGER_HPP

#include "money.hpp"

#include <memory>
#include <string>

namespace ledger {

// Forward declarations
struct account_t;
struct transaction_t;
namespace internal {
   struct account_t;
   struct ledger_impl_t;
} // namespace internal

struct ledger_t {

   ledger_t();

   ledger_t(ledger_t && /*other*/) noexcept;

   ~ledger_t();

   ledger_t& operator=(ledger_t && /*other*/) noexcept;

   money_t get_account_balance(std::string account_name) const;

   ledger_t& operator+=(const account_t& account);

   ledger_t& operator+=(const transaction_t& transaction);

private:
   std::unique_ptr<internal::ledger_impl_t> impl;
};

} // namespace ledger

#endif // COCLES_LEDGER_LEDGER_HPP
