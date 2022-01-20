// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_TABLEVIEW_HPP
#define COCLES_LEDGER_INTERNAL_TABLEVIEW_HPP

#include "EntryProxy.hpp"
#include "ledger/identifier.hpp"

struct Database;
namespace ledger {
namespace internal {
template <typename TYPE>
struct RecordKeeper;
} // namespace internal
} // namespace ledger

template <typename TYPE>
struct TableView {

  explicit TableView(const ledger::internal::RecordKeeper<TYPE>& database);

  struct Iterator {
    explicit Iterator(const ledger::internal::RecordKeeper<TYPE>& t);

    bool operator!=(const Iterator& other) const;

    Iterator& operator++();

    ledger::internal::EntryProxy<TYPE> operator*();

  private:
    const ledger::internal::RecordKeeper<TYPE>& table;
    ledger::identifier_t<TYPE> id;
  }; // class Iterator

  Iterator begin();

  Iterator end();

  bool is_empty() const;

private:
  const ledger::internal::RecordKeeper<TYPE>& records;
}; // struct TableView

template <typename TYPE>
TableView<TYPE>::TableView(const ledger::internal::RecordKeeper<TYPE>& table)
  : records(table) {}

template <typename TYPE>
TableView<TYPE>::Iterator::Iterator(const ledger::internal::RecordKeeper<TYPE>& t)
  : table(t)
  , id(t.used_id) {}

template <typename TYPE>
bool TableView<TYPE>::Iterator::operator!=(const Iterator& other) const {
  return !(id == other.id);
}

template <typename TYPE>
typename TableView<TYPE>::Iterator& TableView<TYPE>::Iterator::operator++() {
  id = table.get_next(id);
  return *this;
}

template <typename TYPE>
ledger::internal::EntryProxy<TYPE> TableView<TYPE>::Iterator::operator*() {
  return ledger::internal::EntryProxy<TYPE>(id);
}

template <typename TYPE>
typename TableView<TYPE>::Iterator TableView<TYPE>::begin() {
  return ++Iterator(records);
}

template <typename TYPE>
typename TableView<TYPE>::Iterator TableView<TYPE>::end() {
  return Iterator(records);
}

template <typename TYPE>
bool TableView<TYPE>::is_empty() const {
  return records.is_empty();
}
#endif // COCLES_LEDGER_INTERNAL_TABLE_HPP
