// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef COCLES_LEDGER_IDENTIFIER_HPP
#define COCLES_LEDGER_IDENTIFIER_HPP

#include <cstdint>
#include <ostream>

namespace ledger {

template <typename TYPE>
struct identifier_t {

  constexpr explicit identifier_t(uint64_t value) noexcept
    : m_value(value) {}

  bool operator==(const identifier_t& other) const noexcept { return (m_value == other.m_value); }

  bool operator!=(const identifier_t& other) const noexcept { return !operator==(other); }

  explicit operator uint64_t() const noexcept { return m_value; }

  bool operator<(const identifier_t& other) const noexcept { return (m_value < other.m_value); }

private:
  uint64_t m_value;
}; // struct identifier_t

template <typename TYPE>
std::ostream& operator<<(std::ostream& out, const identifier_t<TYPE>& id) {
  return out << static_cast<uint64_t>(id);
}

} // namespace ledger

#endif // COCLES_LEDGER_IDENTIFIER_HPP
