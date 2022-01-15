// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_INTERNAL_LISTNODE_HPP
#define COCLES_LEDGER_INTERNAL_LISTNODE_HPP

#include "ledger/identifier.hpp"

#include <cstddef> // size_t
#include <stdexcept>

namespace ledger {

namespace internal {

template <typename TYPE>
struct ListNode {

   constexpr ListNode()
      : m_next(0)
      , m_prev(0)
      , m_data() {}

   constexpr ListNode(identifier_t<TYPE> next, identifier_t<TYPE> prev, bool p_free)
      : m_next(next)
      , m_prev((static_cast<uint64_t>(prev) << 1) | (p_free & 1))
      , m_data() {}

   void set_free(bool free) {
      m_prev |= 1 & free;
   }

   bool get_free() const {
      return m_prev & 1;
   }

   identifier_t<TYPE>& next() {
      return m_next;
   }

   const identifier_t<TYPE>& next() const {
      return m_next;
   }

   void set_prev(identifier_t<TYPE> id) {
      size_t temp = static_cast<uint64_t>(id);
      // TODO: Figure out how to eliminate this check and thrown exception
      if (std::numeric_limits<int64_t>::max() < temp) {
         throw std::overflow_error("Identifier is too large");
      }
      m_prev = (temp << 1) | (m_prev & 1);
   }

   const identifier_t<TYPE> get_prev() const {
      return identifier_t<TYPE>(m_prev >> 1);
   }

   TYPE& data() {
      return m_data;
   }

   const TYPE& data() const {
      return m_data;
   }

private:
   identifier_t<TYPE> m_next;
   size_t m_prev;
   TYPE m_data;
}; // struct ListNode

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_LISTNODE_HPP
