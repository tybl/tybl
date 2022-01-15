// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP
#define COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP

#include "ledger/identifier.hpp"
#include "ListNode.hpp"

#include <vector>

namespace ledger {

namespace internal {

template <typename TYPE>
struct RecordKeeper {
   using id_t = identifier_t<TYPE>;
   using node_t = ListNode<TYPE>;

   static constexpr id_t used_id{0};

   static constexpr id_t free_id{1};

   constexpr RecordKeeper()
      : records({ node_t(used_id, used_id, false), node_t(free_id, free_id, true) })
      , used_count(0) {}

   TYPE& get_record(id_t id) {
      return at(id).data();
   }

   const TYPE& get_record(id_t id) const {
      return at(id).data();
   }

   bool is_empty() const {
      return (0 == used_count);
   }

   size_t get_used_count() const {
      return used_count;
   }

   size_t size() const {
      return records.size() - 2; // First two used for bookkeeping
   }

   id_t get_first_free() const {
      return at(free_id).next();
   }

   id_t get_first_used() const {
      return at(used_id).next();
   }

   id_t get_next(id_t id) const {
      return at(id).next();
   }

   id_t get_prev(id_t id) const {
      return at(id).prev();
   }

   bool is_free(id_t id) const {
      return at(id).get_free();
   }

   bool is_used(id_t id) const {
      return (1 < static_cast<uint64_t>(id)) &&
             (static_cast<uint64_t>(id) < records.size()) &&
             !at(id).get_free();
   }

   void use(id_t id) {
      node_t& record_being_used = at(id);
      record_being_used.set_free(false); // It is no longer available

      // The record used to point to available nodes with next and prev,
      // now the available nodes at next and prev need to point to each other
      at(record_being_used.get_prev()).next() = record_being_used.next();
      at(record_being_used.next()).set_prev(record_being_used.get_prev());

      // The record needs to point to elements in the used list
      // I think this inserts the record at the beginning of the list...
      // TODO: Determine if values assigned to next and prev should be swapped
      record_being_used.next() = at(used_id).next();
      record_being_used.set_prev(used_id);

      // The used list needs to point to the record
      at(at(used_id).next()).set_prev(id);
      at(used_id).next() = id;

      used_count++;
   }

   void free(id_t id) {
      node_t& record_being_freed = at(id);
      record_being_freed.set_free(true);

      at(record_being_freed.get_prev()).next() = record_being_freed.next();
      at(record_being_freed.next()).set_prev(record_being_freed.get_prev());

      record_being_freed.next() = at(free_id).next();
      record_being_freed.set_prev(free_id);

      at(at(free_id).next()).set_prev(id);
      at(free_id).next() = id;

      used_count--;
   }

   id_t allocate() {
      auto id = get_first_free();
      if (id == free_id) {
         push_back();
         id = at(free_id).next();
      }
      use(id);
      return id;
   }

private:

   void push_back() {
      identifier_t<TYPE> id(records.size());
      records.emplace_back(at(free_id).next(), free_id, true);

      at(at(free_id).next()).set_prev(id);
      at(free_id).next() = id;
   }

   node_t& at(identifier_t<TYPE> id) {
      return records.at(static_cast<uint64_t>(id));
   }

   const node_t& at(identifier_t<TYPE> id) const {
      return records.at(static_cast<uint64_t>(id));
   }

private:
   std::vector<node_t> records;
   size_t used_count;
}; // struct RecordKeeper

////////////////// Implementation Details //////////////////

template <typename TYPE>
constexpr identifier_t<TYPE> RecordKeeper<TYPE>::used_id;

template <typename TYPE>
constexpr identifier_t<TYPE> RecordKeeper<TYPE>::free_id;

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP
