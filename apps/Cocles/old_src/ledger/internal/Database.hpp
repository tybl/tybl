// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_DATABASE_HPP
#define COCLES_LEDGER_INTERNAL_DATABASE_HPP

#include "AccountEntry.hpp"
#include "AccountTypeEntry.hpp"
#include "AdjustmentEntry.hpp"
#include "FilteredTableView.hpp"
#include "RecordKeeper.hpp"
#include "TransactionEntry.hpp"

template <typename TYPE>
struct TableView;

struct Database {

  Database();

  // Methods for querying AccountTypes
  TableView<AccountType> get_account_type_table() const;

  const std::string& get_name(AccountTypeEntry record) const;

  AccountTypeEntry find_account_type_by_name(const std::string& name) const;

  // Methods for interacting with Accounts
  TableView<Account> get_account_table() const;

  AccountEntry new_account();

  AccountEntry new_account(const std::string& name, AccountTypeEntry type);

  void clear_account_table();

  void delete_account(AccountEntry record);

  const std::string& get_name(AccountEntry record) const;

  void set_name(AccountEntry record, const std::string& name);

  AccountEntry find_account_by_name(const std::string& name) const;

  AccountTypeEntry get_type(AccountEntry record) const;

  void set_type(AccountEntry record, AccountTypeEntry type);

  // TODO(tybl): find_account_by_type should be able to return many AccountEntrys
  FilteredTableView<Account> find_account_by_type(AccountTypeEntry type) const;

  // Methods for interacting with Transactions
  TableView<Transaction> get_transaction_table() const;

  TransactionEntry new_transaction();

  TransactionEntry new_transaction(const date::year_month_day& date, const std::string& memo);

  void clear_transaction_table();

  void delete_transaction(TransactionEntry record);

  const date::year_month_day get_date(TransactionEntry record) const;

  void set_date(TransactionEntry record, const date::year_month_day& date);

  // TODO(tybl): find_transaction_by_date should be able to return many TransactionEntrys
  FilteredTableView<Transaction> find_transaction_by_date(const date::year_month_day& date) const;

  const std::string& get_memo(TransactionEntry record) const;

  void set_memo(TransactionEntry record, const std::string& memo);

  TransactionEntry find_transaction_by_memo(const std::string& memo) const;

  // Methods for interacting with Adjustments
  TableView<Adjustment> get_adjustment_table() const;

  AdjustmentEntry new_adjustment();

  AdjustmentEntry new_adjustment(AccountEntry account, TransactionEntry transaction);

  void clear_adjustment_table();

  void delete_adjustment(AdjustmentEntry record);

  AccountEntry get_account(AdjustmentEntry record) const;

  void set_account(AdjustmentEntry record, AccountEntry account);

  // TODO(tybl): find_adjustment_by_account shoule be able to return many AdjustmentEntrys
  AdjustmentEntry find_adjustment_by_account(AccountEntry account) const;

  TransactionEntry get_transaction(AdjustmentEntry record) const;

  void set_transaction(AdjustmentEntry record, TransactionEntry transaction);

  // TODO(tybl): find_adjustment_by_transaction should be able to return many AdjustmentEntrys
  AdjustmentEntry find_adjustment_by_transaction(TransactionEntry transaction) const;

private:
  ledger::internal::RecordKeeper<Account> account_table;
  ledger::internal::RecordKeeper<AccountType> account_type_table;
  ledger::internal::RecordKeeper<Adjustment> adjustment_table;
  ledger::internal::RecordKeeper<Transaction> transaction_table;
};

#endif // COCLES_LEDGER_INTERNAL_DATABASE_HPP
