// License: The Unlicense (https://unlicense.org)
#ifndef COCLES_LEDGER_PARSE_TRANSACTION_HPP
#define COCLES_LEDGER_PARSE_TRANSACTION_HPP

#include "adjustment.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <memory>
#include <string>
#include <vector>

namespace ledger {

namespace parse {

class Transaction {
   struct PassKey {};
public:
   using date_t = boost::gregorian::date;

   explicit Transaction(std::string const& t);
   Transaction(PassKey /* private */, date_t date, std::string payee);

   [[nodiscard]] date_t date() const;

   [[nodiscard]] const std::string& payee() const;

   static std::unique_ptr<Transaction> parse(std::string const& t);
   static Transaction parse(std::istream& stream);

private:
   date_t                    m_date;
   std::string               m_payee;
   std::vector<adjustment_t> m_adjustments;
}; // struct Transaction

} // namespace parse

// TODO(tblyons): Move the parse function to another file. Probably src/ledger/parse.hpp
inline
ledger::parse::Transaction Parse(std::string const& input) {
   return ledger::parse::Transaction(input);
} // parse(std::string input)

} // namespace ledger

#endif // COCLES_LEDGER_PARSE_TRANSACTION_HPP
