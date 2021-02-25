// License: The Unlicense (https://unlicense.org)
#ifndef COCLES_LEDGER_ACCOUNT_HPP
#define COCLES_LEDGER_ACCOUNT_HPP

#include <memory>
#include <string>

namespace ledger {

struct Account {

   explicit Account(std::string name);

   [[nodiscard]] std::string const& name() const;

   [[nodiscard]] bool operator<(Account const& other) const;

   [[nodiscard]] bool operator==(Account const& other) const;

private:
   std::string m_name;
}; // struct Account

} // namespace ledger

#endif // COCLES_LEDGER_ACCOUNT_HPP
