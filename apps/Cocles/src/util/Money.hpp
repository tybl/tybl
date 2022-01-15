// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_UTIL_MONEY_HPP
#define TYBL_COCLES_UTIL_MONEY_HPP

///////////////////////////////////////////////////////////////////////////////
// Defines class to represent money
//
// Only represent up to 1,000,000,000,000,000.000
//
// Use cases:
// - Sum up amounts from each adjustment for a specific account
// - Convert to a string for display
///////////////////////////////////////////////////////////////////////////////

#include <string>

namespace util {

struct Money {
   using MoneyType = std::string;

   Money();

   explicit Money(MoneyType const& v);

   explicit Money(int64_t v);

   // Comparison Operators
   bool operator==(Money const& o) const;
   bool operator!=(Money const& o) const;
   bool operator<(Money const& o) const;
   bool operator>(Money const& o) const;
   bool operator<=(Money const& o) const;
   bool operator>=(Money const& o) const;

   // Arithmetic Operators
   Money& operator+=(Money const& o);
   Money& operator-=(Money const& o);
   //Money& operator *= (Money const& o);
   //Money& operator %= (Money const& o);
   //Money& operator /= (Money const& o);
   //Money& operator+=(int64_t o);
   //Money& operator-=(int64_t o);
   Money& operator*=(int64_t o);
   Money& operator%=(int64_t o);
   Money& operator/=(int64_t o);

   [[nodiscard]] MoneyType get_money_type() const;
   void set_money_type(MoneyType const& v);

   friend void swap(Money& a, Money& b);

private:
   int64_t m_value{0};
}; // struct Money

Money operator+(Money a, Money const& b);

std::ostream& operator<<(std::ostream& s, Money const& m);
std::istream& operator>>(std::istream& s, Money& m);

} // namespace util

#endif // TYBL_COCLES_UTIL_MONEY_HPP
