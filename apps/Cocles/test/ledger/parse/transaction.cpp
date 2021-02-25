// License: The Unlicense (https://unlicense.org)
#include "../src/ledger/parse/transaction.hpp"

#include "doctest/doctest.h"

TEST_CASE("parse::Transaction") {
#if 0
   using namespace std::string_literals;
   auto str = "2019-03-05 Wegman's\n    Accounts:Citi:Credit   $-4.35\n    Funds:Daily:Food   $4.35\n\n"s;
   auto trans = ledger::Parse(str);
   CHECK(trans.date().year() == 2019);
   CHECK(trans.date().month() == boost::gregorian::Mar);
   CHECK(trans.date().day() == 5);
   CHECK(trans.payee() == "Wegman's"s);
   auto tran_ptr = ledger::parse::Transaction::parse(str);
   CHECK(tran_ptr->date().year() == 2019);
   CHECK(tran_ptr->date().month() == boost::gregorian::Mar);
   CHECK(tran_ptr->date().day() == 5);
   CHECK(tran_ptr->payee() == "Wegman's"s);
#endif
} // TEST_CASE("parse::Transaction")
