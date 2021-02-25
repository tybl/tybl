// License: The Unlicense (https://unlicense.org)
#include "Database.hpp"

#include "TableView.hpp"

Database::Database() {
   account_type_table.get_record(account_type_table.allocate()).name = "Income/Expense";
   account_type_table.get_record(account_type_table.allocate()).name = "Unbudgeted Asset";
   account_type_table.get_record(account_type_table.allocate()).name = "Budgeted Asset";
   account_type_table.get_record(account_type_table.allocate()).name = "Budget Category";
}

// Methods for interacting with AccountTypes
TableView<AccountType> Database::get_account_type_table() const {
   return TableView<AccountType>(account_type_table);
}

const std::string& Database::get_name(AccountTypeEntry record) const {
   return account_type_table.get_record(record.get_id()).name;
}

AccountTypeEntry Database::find_account_type_by_name(const std::string& name) const {
   for (auto account_type : get_account_type_table()) {
      if (get_name(account_type) == name) {
         return account_type;
      }
   }
   return AccountTypeEntry(ledger::identifier_t<AccountType>(0));
}

// Methods for interacting with Accounts
TableView<Account> Database::get_account_table() const {
   return TableView<Account>(account_table);
}

AccountEntry Database::new_account() {
   return AccountEntry(account_table.allocate());
}

AccountEntry Database::new_account(const std::string& name, AccountTypeEntry type) {
   AccountEntry result(account_table.allocate());
   account_table.get_record(result.get_id()).name = name;
   account_table.get_record(result.get_id()).type = type;
   return result;
}

void Database::clear_account_table() {
   while (!get_account_table().is_empty()) {
      delete_account(*get_account_table().begin());
   }
}

void Database::delete_account(AccountEntry record) {
   account_table.free(record.get_id());
}

const std::string& Database::get_name(AccountEntry record) const {
   return account_table.get_record(record.get_id()).name;
}

void Database::set_name(AccountEntry record, const std::string& name) {
   account_table.get_record(record.get_id()).name = name;
}

AccountEntry Database::find_account_by_name(const std::string& name) const {
   for (auto account : get_account_table()) {
      if (get_name(account) == name) {
         return account;
      }
   }
   return AccountEntry(ledger::identifier_t<Account>(0));
}

AccountTypeEntry Database::get_type(AccountEntry record) const {
   return account_table.get_record(record.get_id()).type;
}

void Database::set_type(AccountEntry record, AccountTypeEntry type) {
   account_table.get_record(record.get_id()).type = type;
}

FilteredTableView<Account> Database::find_account_by_type(AccountTypeEntry type) const {
   return FilteredTableView<Account>(account_table, [type] (const Account& a) -> bool { return a.type == type; });
}

// Methods for interacting with Transactions
TableView<Transaction> Database::get_transaction_table() const {
   return TableView<Transaction>(transaction_table);
}

TransactionEntry Database::new_transaction() {
   return TransactionEntry(transaction_table.allocate());
}

TransactionEntry Database::new_transaction(const date::year_month_day& date, const std::string& memo) {
   TransactionEntry result(transaction_table.allocate());
   transaction_table.get_record(result.get_id()).date = date;
   transaction_table.get_record(result.get_id()).memo = memo;
   return result;
}

void Database::clear_transaction_table() {
   while (!get_transaction_table().is_empty()) {
      delete_transaction(*get_transaction_table().begin());
   }
}

void Database::delete_transaction(TransactionEntry record) {
   transaction_table.free(record.get_id());
}

const date::year_month_day Database::get_date(TransactionEntry record) const {
   //assert(!record.is_null());
   return transaction_table.get_record(record.get_id()).date;
}

void Database::set_date(TransactionEntry record, const date::year_month_day& date) {
   //assert(!record.is_null());
   transaction_table.get_record(record.get_id()).date = date;
}

const std::string& Database::get_memo(TransactionEntry record) const {
   //assert(!record.is_null());
   return transaction_table.get_record(record.get_id()).memo;
}

void Database::set_memo(TransactionEntry record, const std::string& memo) {
   //assert(!record.is_null());
   transaction_table.get_record(record.get_id()).memo = memo;
}

// Methods for interacting with Adjustments
TableView<Adjustment> Database::get_adjustment_table() const {
   return TableView<Adjustment>(adjustment_table);
}

AdjustmentEntry Database::new_adjustment() {
   return AdjustmentEntry(adjustment_table.allocate());
}

AdjustmentEntry Database::new_adjustment(AccountEntry account, TransactionEntry transaction) {
   AdjustmentEntry result(adjustment_table.allocate());
   adjustment_table.get_record(result.get_id()).account = account;
   adjustment_table.get_record(result.get_id()).transaction = transaction;
   return result;
}

void Database::clear_adjustment_table() {
   while (!get_adjustment_table().is_empty()) {
      delete_adjustment(*get_adjustment_table().begin());
   }
}

void Database::delete_adjustment(AdjustmentEntry record) {
   adjustment_table.free(record.get_id());
}

AccountEntry Database::get_account(AdjustmentEntry record) const {
   return adjustment_table.get_record(record.get_id()).account;
}

void Database::set_account(AdjustmentEntry record, AccountEntry account) {
   adjustment_table.get_record(record.get_id()).account = account;
}

AdjustmentEntry Database::find_adjustment_by_account(AccountEntry account) const {
   for (auto adjustment : get_adjustment_table()) {
      if (get_account(adjustment) == account) {
         return adjustment;
      }
   }
   return AdjustmentEntry(ledger::identifier_t<Adjustment>(0));
}

TransactionEntry Database::get_transaction(AdjustmentEntry record) const {
   return adjustment_table.get_record(record.get_id()).transaction;
}

void Database::set_transaction(AdjustmentEntry record, TransactionEntry transaction) {
   adjustment_table.get_record(record.get_id()).transaction = transaction;
}

AdjustmentEntry Database::find_adjustment_by_transaction(TransactionEntry transaction) const {
   for (auto adjustment : get_adjustment_table()) {
      if (get_transaction(adjustment) == transaction) {
         return adjustment;
      }
   }
   return AdjustmentEntry(ledger::identifier_t<Adjustment>(0));
}

// Test cases
#include "doctest/doctest.h"

#include <iostream>

TEST_CASE("Database::transaction::memo dogfood") {
   Database db;
   auto first_trans = db.new_transaction();
   std::string input = "Hello world!";
   db.set_memo(first_trans, input);
   CHECK(input == db.get_memo(first_trans));
}

TEST_CASE("Database::account_type list each") {
   Database db;
   std::string input("Income/Expense");
   auto record = db.find_account_type_by_name(input);
   CHECK(db.get_name(record) == input);
   input = "Unbudgeted Asset";
   record = db.find_account_type_by_name(input);
   CHECK(db.get_name(record) == input);
   input = "Budgeted Asset";
   record = db.find_account_type_by_name(input);
   CHECK(db.get_name(record) == input);
   input = "Budget Category";
   record = db.find_account_type_by_name(input);
   CHECK(db.get_name(record) == input);
}

TEST_CASE("Database::account list each") {
   Database db;
   auto budgeted_asset = db.find_account_type_by_name("Budgeted Asset");
   auto income_expense = db.find_account_type_by_name("Income/Expense");
   db.new_account("Expense::Walmart", income_expense);
   db.new_account("Asset::Credit Card", budgeted_asset);
   db.new_account("Expense::Target", income_expense);
   db.new_account("Asset::Checking", budgeted_asset);
   db.new_account("Expense::Whole Foods", income_expense);
   db.new_account("Asset::Savings", budgeted_asset);
   db.new_account("Expense::Subway", income_expense);
   db.new_account("Expense::McDonald's", income_expense);
   size_t budgeted_asset_count = 0;
   auto budgeted_asset_table = db.find_account_by_type(budgeted_asset);
   for (auto a : budgeted_asset_table) {
      CHECK(db.get_name(a).find("Asset") != std::string::npos);
      static_cast<void>(a);
      budgeted_asset_count += 1;
   }
   CHECK(budgeted_asset_count == 3);
   size_t income_expense_count = 0;
   auto income_expense_table = db.find_account_by_type(income_expense);
   for (auto a : income_expense_table) {
      CHECK(db.get_name(a).find("Expense") != std::string::npos);
      static_cast<void>(a);
      income_expense_count += 1;
   }
   CHECK(income_expense_count == 5);
}
