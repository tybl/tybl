# Notes
* Return types for queries:
    * View Objects:
        * http://www.drdobbs.com/cpp/c-view-objects/196513737
        * https://scarvenger.wordpress.com/2008/11/14/c-container-view/
    * https://www.fluentcpp.com/?s=filter+iterator

# Use cases
* Add account
* Add transaction
* List accounts
* List budget categories
* List payees
* List transactions for a payee
* List adjustments for an account
* Sum balance for transaction
* Sum balances for accounts
* Sum balances for budget categories

# Interface
## Add account
ledger-cli (in a file):
```
account Funds:Daily:Food
```

cocles source code
```
db.insert(Account("Funds:Daily:Food"));
```
## Add payee
ledger-cli (in a file):
```
payee Wegman's
```

cocles source code
```
db.insert(Payee("Wegman's"));
```
## List accounts
ledger-cli (commandline)
```
$ ledger accounts regex
```

cocles source code
```
auto accounts = db.accounts("regex");
for (auto const& a : accounts) {
    std::cout << a.name() << "\n";
}
```

## List payees

ledger-cli (commandline)
```
$ ledger payees regex
```

cocles source code
```
auto payees = db.payees("regex");
for (auto const& p : payees) {
    std::cout << p.name() << "\n";
}
```

## List transactions for a payee
ledger-cli (commandline)
```
$ ledger ...
```

## List adjustments for an account
ledger-cli (commandline)
```
$ ledger reg regex
```

cocles source code
```
auto accounts = db.accounts("regex");
for (auto const& a : accounts) {
    auto adjustments = db.adjustments(a);
    Money sum;
    for (auto const& adj : adjustments) {
        std::cout << adj.date() << " "
                  << adj.payee().name() << " "
                  << a.name() << " "
                  << adj.amount() << " "
                  << sum += adj.amount() << "\n";
    }
}
```

## Sum balance for transaction
ledger-cli (commandline)
```
$ ledger ...
```

## Sum balances for accounts
ledger-cli (commandline)
```
$ ledger equity regex
```

cocles source code
```
auto accounts = db.accounts("regex");
for (auto const& a : accounts) {
    auto adjustments = db.adjustments(a);
    std::accumulate(adjustments, Money());
    std::cout << a.name() << " " << sum << "\n";
}
```

# Extended Adjustments Table Plus
A range of extended Adjustment objects appears to work well, except that accounts and payees cannot be added outside of a transaction.
It is important that accounts can be added outside of a transaction so they can be used for verification (i.e. only allow a transaction to be added if the account already exists).
The extended adjustments table scheme could be enhanced in the following ways to enable account and payee verification:
```
struct {
struct Account {
    std::string name;
}; // struct Account

std::set<Account> accounts; // Should this be a list?

struct Payee {
    std::string name;
}; // struct Payee

std::list<Payee> payees;

struct Adjustment {
    boost::date date;
    /*pointer/reference/iterator*/ payee;
    /*pointer/reference/iterator*/ account;
    Money amount;
}; // struct Adjustment

std::vector<Adjustment> adjustments;
} database;
```
* Add account
```
void Database::Add(Account account) {
    // Only insert if it doesn't already exist
    accounts.insert(account);
}
```
* Add payee
```
void Database::Add(Payee payee) {
    // Only insert if it doesn't already exist
    payees.insert(payee);
}
```
* Add transaction
* List accounts
```
std::vector<AccountProxy> accounts(std::string re) {
    std::vector<AccountProxy> result;
    util::copy_iterator_if(accounts, result,
                           [re](Account const& account){
                              return std::regex_search(account.name(). std::regex(re)); });
    return result;
}
```
* List payees
```
std::vector<PayeeProxy> accounts(std::string re) {
    std::vector<PayeeProxy> result;
    util::copy_iterator_if(accounts, result,
                           [re](Payee const& payee){
                              return std::regex_search(payee.name(). std::regex(re)); }); // TODO: Move creation of regex out of loop
    return result;
}
```