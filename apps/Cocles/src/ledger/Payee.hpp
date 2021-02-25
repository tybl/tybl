// License: The Unlicense (https://unlicense.org)
#ifndef COCLES_LEDGER_PAYEE_HPP
#define COCLES_LEDGER_PAYEE_HPP

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

#endif // COCLES_LEDGER_PAYEE_HPP
