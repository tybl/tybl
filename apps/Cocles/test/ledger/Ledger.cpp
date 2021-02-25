// License: The Unlicense (https://unlicense.org)
#include "ledger/Ledger.hpp"

#include "ledger/Account.hpp"
#include "ledger/Payee.hpp"
#include "ledger/Transaction.hpp"
#include "ledger/transaction/Builder.hpp"

#include "doctest/doctest.h"

TEST_CASE("tblyons/cocles#4") {
   using namespace ledger;
   Ledger ledger;

   Account accounts_citi_credit("Accounts:Citi:Credit");
   Account funds_daily_food("Funds:Daily:Food");
   Payee payee_wegmans("Wegman's");

   ledger.insert(accounts_citi_credit);
   ledger.insert(funds_daily_food);
   ledger.insert(payee_wegmans);

   ledger.insert(Transaction::Builder().set_date("2019-03-09").set_payee("Wegman's")
         .add_adjustment(Adjustment(Account("Accounts:Citi:Credit"), util::Money("-54.33 USD")))
         .add_adjustment(Adjustment(Account("Funds:Daily:Food"), util::Money("54.33 USD")))
         .build());

   auto payees = ledger.payees("");
   auto prior_size = payees.size();
   std::sort(payees.begin(), payees.end());
   auto new_end = std::unique(payees.begin(), payees.end());
   payees.erase(new_end, payees.end());
   auto post_size = payees.size();
   CHECK(prior_size == post_size);
}

TEST_CASE("tblyons/cocles#5") {
   using namespace ledger;
   Ledger ledger;

   Account accounts_citi_credit("Accounts:Citi:Credit");
   Account funds_daily_food("Funds:Daily:Food");
   Payee payee_wegmans("Wegman's");

   ledger.insert(accounts_citi_credit);
   ledger.insert(funds_daily_food);
   ledger.insert(payee_wegmans);

   auto t = Transaction::Builder().set_date("2019-03-09").set_payee("Wegman's")
         .add_adjustment(Adjustment(Account("Accounts:Citi:Credit"), util::Money("-54.33 USD")))
         .add_adjustment(Adjustment(Account("Funds:Daily:Food"), util::Money("54.33 USD")))
         .build();

   ledger.insert(t);
   ledger.insert(t);

   auto accounts = ledger.accounts("");
   auto prior_size = accounts.size();
   std::sort(accounts.begin(), accounts.end());
   auto new_end = std::unique(accounts.begin(), accounts.end());
   accounts.erase(new_end, accounts.end());
   auto post_size = accounts.size();
   CHECK(prior_size == post_size);
}
