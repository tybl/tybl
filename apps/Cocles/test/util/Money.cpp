// License: The Unlicense (https://unlicense.org)
#include "util/Money.hpp"

#include "doctest/doctest.h"

#include <iostream>
#include <sstream>

using namespace util;

TEST_CASE("Money::Money(),Money::Money(int64_t),Money::operator==(Money const&)") { CHECK(Money() == Money(0)); }

TEST_CASE("Money::Money(),Money::Money(std::string const&),Money::operator==(Money const&)") {
  CHECK(Money() == Money("0"));
}

TEST_CASE("Money::Money(),Money::operator*=(int64_t),Money::operator==(Money const&)") {
  CHECK((Money() *= 4) == Money());
}

TEST_CASE("Money::Money(int64_t),Money::operator*=(int64_t),Money::operator==(Money const&)") {
  CHECK((Money(16) *= 4) == Money(64));
}

TEST_CASE("Money::Money(int64_t),Money::operator*=(int64_t),Money::operator!=(Money const&)") {
  CHECK(!((Money(16) *= 4) != Money(64)));
  CHECK((Money(16) *= 4) != Money());
}

TEST_CASE("Money::Money(int64_t),Money::operator/=(int64_t),Money::operator<=(Money const&)") {
  CHECK((Money(16) /= 4) <= Money(4));
}

TEST_CASE("std::ostream& operator<<(std::ostream&,Money const&)") {
  const std::string s = "123456";
  std::stringstream ss;
  ss << Money(s);
  CHECK(ss.str() == "$1,234.56");
}

TEST_CASE("std::istream& operator>>(std::istream&, Money&)") {
  std::stringstream ss("$1,234.56");
  Money m;
  try {
    ss >> m;
  } catch (std::invalid_argument& e) {
    std::cout << "Threw invalid_argument: " << e.what() << std::endl;
  } catch (std::out_of_range& e) {
    std::cout << "Threw out_of_range: " << e.what() << std::endl;
  } catch (std::domain_error& e) {
    std::cout << "Threw domain_error: " << e.what() << std::endl;
  } catch (std::length_error& e) {
    std::cout << "Threw length_error: " << e.what() << std::endl;
  } catch (std::logic_error& e) {
    std::cout << "Threw logic_error: " << e.what() << std::endl;
  } catch (std::exception& e) {
    std::cout << "Threw exception: " << e.what() << std::endl;
  }
  CHECK(m.get_money_type() == "123456");
}
