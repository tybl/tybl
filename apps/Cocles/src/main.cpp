// License: The Unlicense (https://unlicense.org)
#include "ledger/Account.hpp"
#include "ledger/Adjustment.hpp"
#include "ledger/Ledger.hpp"
#include "ledger/Payee.hpp"
#include "ledger/Transaction.hpp"
#include "ledger/transaction/Builder.hpp"
#include "util/Date.hpp"
#include "util/Money.hpp"

int main(int argc, const char* argv[], const char* envp[]) {
  using namespace ledger;
  static_cast<void>(argc);
  static_cast<void>(argv);
  static_cast<void>(envp);

  Ledger ledger;

  Account accounts_citi_credit("Accounts:Citi:Credit");
  Account funds_daily_food("Funds:Daily:Food");
  Payee payee_wegmans("Wegman's");

  ledger.insert(accounts_citi_credit);
  ledger.insert(funds_daily_food);
  ledger.insert(payee_wegmans);

  ledger.insert(Transaction::Builder()
                    .set_date("2019-03-09")
                    .set_payee("Wegman's")
                    .add_adjustment(Adjustment(Account("Accounts:Citi:Credit"), util::Money("-54.33 USD")))
                    .add_adjustment(Adjustment(Account("Funds:Daily:Food"), util::Money("54.33 USD")))
                    .build());

  for (auto const& a : ledger.accounts("")) {
    std::cout << a.name() << "\n";
  }

  for (auto const& p : ledger.payees("")) {
    std::cout << p.name() << "\n";
  }

  std::stringstream input_file(
      "2019-05-05 Giant\n"
      "    * Accounts:Citi:Credit                         $-4.63\n"
      "    Funds:Daily:Petrol\n");

  input_file >> ledger;

  return 0;
}
