// License: The Unlicense (https://unlicense.org)
#include "ledger/transaction/Builder.hpp"

#include "doctest/doctest.h"

TEST_CASE("tybl/cocles#3") {
   using namespace ledger;

   CHECK(Transaction::Builder().set_date("2019-03-09").set_payee("Wegman's")
         .add_adjustment(Adjustment(Account("Accounts:Citi:Credit"), util::Money("-54.33 USD")))
         .add_adjustment(Adjustment(Account("Funds:Daily:Food"), util::Money("54.33 USD")))
         .is_valid());
   CHECK(!Transaction::Builder().set_date("2019-03-09").set_payee("Wegman's")
         .add_adjustment(Adjustment(Account("Funds:Daily:Food"), util::Money("54.33 USD")))
         .is_valid());
}
