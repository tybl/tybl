// License: The Unlicense (https://unlicense.org)
#include "Money.hpp"

#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>

namespace util {

struct space_out
   : std::moneypunct<char>
{
   pattern do_pos_format() const override {
      return { { symbol, sign, value, none } };
   }

   pattern do_neg_format() const override {
      return { { symbol, sign, value, none } };
   }

   int do_frac_digits() const override {
      return 2;
   }

   char_type do_thousands_sep() const override {
      return ',';
   }

   string_type do_grouping() const override {
      return "\003";
   }

   string_type do_curr_symbol() const override {
      return "$";
   }
};

Money::Money() = default;

Money::Money(MoneyType const& v)
   : m_value(std::stoll(v))
{ }

Money::Money(int64_t v)
   : m_value(v)
{ }

bool Money::operator==(Money const& o) const {
   return m_value == o.m_value;
}

bool Money::operator!=(Money const& o) const {
   return m_value != o.m_value;
}

bool Money::operator<(Money const& o) const {
   return m_value < o.m_value;
}

bool Money::operator>(Money const& o) const {
   return m_value > o.m_value;
}

bool Money::operator<=(Money const& o) const {
   return m_value <= o.m_value;
}

bool Money::operator>=(Money const& o) const {
   return m_value >= o.m_value;
}

Money& Money::operator+=(Money const& other) {
   m_value += other.m_value;
   return *this;
}

Money& Money::operator-=(Money const& other) {
   m_value -= other.m_value;
   return *this;
}

//Money& operator %= (Money const& other);
//Money& operator /= (Money const& other);

Money& Money::operator*=(int64_t other) {
   m_value *= other;
   return *this;
}

Money& Money::operator%=(int64_t other) {
   m_value %= other;
   return *this;
}

Money& Money::operator/=(int64_t other) {
   m_value /= other;
   return *this;
}

Money::MoneyType Money::get_money_type() const {
   return std::to_string(m_value);
}

void Money::set_money_type(MoneyType const& v) {
   m_value = std::stoll(v);
}

void swap(Money& a, Money& b) {
   using std::swap;
   swap(a.m_value, b.m_value);
}

Money operator+(Money a, Money const& b) {
   return a += b;
}

std::ostream& operator<<(std::ostream& s, Money const& m) {
   if (!std::has_facet<space_out>(s.getloc())) {
      s.imbue(std::locale(s.getloc(), new space_out));
   }
   return s << std::showbase << std::put_money(m.get_money_type());
}

std::istream& operator>>(std::istream& s, Money& m) {
   if (!std::has_facet<space_out>(s.getloc())) {
      s.imbue(std::locale(s.getloc(), new space_out));
   }
   std::string temp;
   s >> std::get_money(temp);
   m.set_money_type(temp);
   return s;
}

} // namespace util
