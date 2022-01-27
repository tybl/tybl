// License: The Unlicense (https://unlicense.org)
#include "Builder.hpp"

#include "ledger/Transaction.hpp"

#include <iostream>
#include <numeric>

namespace ledger {

Transaction::Builder& Transaction::Builder::set_date(util::Date date) {
  m_date = date;
  return *this;
}

Transaction::Builder& Transaction::Builder::set_date(std::string const& date) {
  m_date = boost::gregorian::from_string(date);
  return *this;
}

Transaction::Builder& Transaction::Builder::set_payee(Payee payee) {
  m_payee = std::move(payee);
  return *this;
}

Transaction::Builder& Transaction::Builder::set_payee(std::string const& payee) {
  m_payee = Payee(payee);
  return *this;
}

Transaction::Builder& Transaction::Builder::add_adjustment(Adjustment const& adjustment) {
  m_adjustments.push_back(adjustment);
  return *this;
}

bool Transaction::Builder::is_valid() const {
  return util::Money() == std::accumulate(m_adjustments.begin(), m_adjustments.end(), util::Money(),
                                          [](util::Money const& m, Adjustment const& a) -> util::Money {
                                            // std::cout << "T:B:iv: " << m << " + " << a.amount() << " = " << m +
                                            // a.amount() << "\n";
                                            return m + a.amount();
                                          });
}
util::Date const& Transaction::Builder::date() const { return m_date; }

Payee const& Transaction::Builder::payee() const { return m_payee; }

std::vector<Adjustment> const& Transaction::Builder::adjustments() const { return m_adjustments; }

Transaction Transaction::Builder::build() const {
  if (!is_valid()) {
    throw std::runtime_error("Error: Transaction adjustments don't sum to zero");
  }
  return Transaction(*this);
}

std::istream& operator>>(std::istream& s, Transaction::Builder& t) { return s; }

} // namespace ledger
