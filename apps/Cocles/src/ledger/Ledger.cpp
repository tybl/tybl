// License: The Unlicense (https://unlicense.org)
#include "Ledger.hpp"

#include "Account.hpp"
#include "ExtendedAdjustment.hpp"
#include "Payee.hpp"
#include "Transaction.hpp"
#include "transaction/Builder.hpp"
#include "util/transform_if.hpp"

#include <boost/container/flat_set.hpp>

#include <iostream>
#include <istream>
#include <regex>

namespace ledger {

struct Ledger::Impl {

   void insert(Account const& a) { m_accounts.insert(a); }

   void insert(Payee const& p) { m_payees.insert(p); }

   void insert(Transaction const& t) {
      if (is_valid(t)) {
         for (auto const& a : t.adjustments()) {
            m_adjustments.emplace_back(t.date(), t.payee(), a.account(), a.amount());
         }
      } else {
         std::cout << "Error: invalid transaction!\n";
      }
   }

   [[nodiscard]] std::vector<Account> accounts(std::string const& re) const {
      std::vector<Account> result;
      std::copy_if(m_accounts.begin(), m_accounts.end(), std::back_inserter(result),
                   [re](Account const& account) {
                      return std::regex_search(account.name(), std::regex(re)); });
      return result;
   }

   [[nodiscard]] std::vector<Payee> payees(std::string const& re) const {
      std::vector<Payee> result;
      std::copy_if(m_payees.begin(), m_payees.end(), std::back_inserter(result),
                   [re](Payee const& payee) {
                      return std::regex_search(payee.name(), std::regex(re)); });
      return result;
   }

private:
   bool is_valid(Transaction const& t) {
      if (!m_payees.contains(t.payee())) {
         return false;
      }
      for (auto const& a : t.adjustments()) {
         if (!m_accounts.contains(a.account())) {
            return false;
         }
      }
      return true;
   }

private:
   boost::container::flat_set<Account> m_accounts;
   boost::container::flat_set<Payee>   m_payees;
   std::vector<ExtendedAdjustment>     m_adjustments;
};

Ledger::Ledger() : m_pimpl(std::make_shared<Ledger::Impl>()) {}

void Ledger::insert(Account const& a) { m_pimpl->insert(a); }

void Ledger::insert(Payee const& p) { m_pimpl->insert(p); }

void Ledger::insert(Transaction const& t) { m_pimpl->insert(t); }

std::vector<Account> Ledger::accounts(std::string const& re) const { return m_pimpl->accounts(re); }

std::vector<Payee> Ledger::payees(std::string const& re) const { return m_pimpl->payees(re); }

std::istream& operator>>(std::istream& s, Ledger& l) {
   std::string temp;
   while (s) {
      switch (s.peek()) {
         case ' ':
            // Shouldn't be a space on its own
            std::cerr << "case \' \': Found a \"" << s.get() << "\"\n";
            break;
         case '0': [[fallthrough]];
         case '1': [[fallthrough]];
         case '2': [[fallthrough]];
         case '3': [[fallthrough]];
         case '4': [[fallthrough]];
         case '5': [[fallthrough]];
         case '6': [[fallthrough]];
         case '7': [[fallthrough]];
         case '8': [[fallthrough]];
         case '9': {
            // Parse transaction
            Transaction::Builder t;
            s >> t;
            l.insert(t.build());
            break;
         }
         case 'A': [[fallthrough]];
         case 'B': [[fallthrough]];
         case 'C': [[fallthrough]];
         case 'D': [[fallthrough]];
         case 'E': [[fallthrough]];
         case 'F': [[fallthrough]];
         case 'G': [[fallthrough]];
         case 'H': [[fallthrough]];
         case 'I': [[fallthrough]];
         case 'J': [[fallthrough]];
         case 'K': [[fallthrough]];
         case 'L': [[fallthrough]];
         case 'M': [[fallthrough]];
         case 'N': [[fallthrough]];
         case 'O': [[fallthrough]];
         case 'P': [[fallthrough]];
         case 'Q': [[fallthrough]];
         case 'R': [[fallthrough]];
         case 'S': [[fallthrough]];
         case 'T': [[fallthrough]];
         case 'U': [[fallthrough]];
         case 'V': [[fallthrough]];
         case 'W': [[fallthrough]];
         case 'X': [[fallthrough]];
         case 'Y': [[fallthrough]];
         case 'Z': [[fallthrough]];
         case 'a': [[fallthrough]];
         case 'b': [[fallthrough]];
         case 'c': [[fallthrough]];
         case 'd': [[fallthrough]];
         case 'e': [[fallthrough]];
         case 'f': [[fallthrough]];
         case 'g': [[fallthrough]];
         case 'h': [[fallthrough]];
         case 'i': [[fallthrough]];
         case 'j': [[fallthrough]];
         case 'k': [[fallthrough]];
         case 'l': [[fallthrough]];
         case 'm': [[fallthrough]];
         case 'n': [[fallthrough]];
         case 'o': [[fallthrough]];
         case 'p': [[fallthrough]];
         case 'q': [[fallthrough]];
         case 'r': [[fallthrough]];
         case 's': [[fallthrough]];
         case 't': [[fallthrough]];
         case 'u': [[fallthrough]];
         case 'v': [[fallthrough]];
         case 'w': [[fallthrough]];
         case 'x': [[fallthrough]];
         case 'y': [[fallthrough]];
         case 'z':
            // Parse account
            std::cerr << "case \'a\': Found a \"" << static_cast<char>(s.get()) << "\"\n";
            break;
         default:
            std::cerr << "default: Found a \"" << s.get() << "\"\n";
            break;
      }
   } // while (s)
   return s;
}

} // namespace ledger
