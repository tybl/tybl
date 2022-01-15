// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_LEDGER_PAYEE_HPP
#define TYBL_COCLES_LEDGER_PAYEE_HPP

#include <memory>
#include <string>

namespace ledger {

struct Payee {

   Payee() = default;

   explicit Payee(std::string name);

   [[nodiscard]] std::string const& name() const;

   [[nodiscard]] bool operator<(Payee const& other) const;

   [[nodiscard]] bool operator==(Payee const& other) const;

private:
   std::string m_name;
}; // struct Payee

} // namespace ledger

#endif // TYBL_COCLES_LEDGER_PAYEE_HPP
