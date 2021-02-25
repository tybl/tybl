# Considerations
* Arithmetic
    * Addition: The majority of operations will be addition (may be addition of negative values)
    * Rounding: Only necessary for multiplication or division
* Fractionals: Most monetary representations have whole units and fractional units
* Currency representation/codes

# Standards
* IEEE 754-2008 Decimal Floating-Point Arithmetic specification: http://www.dsc.ufcg.edu.br/~cnum/modulos/Modulo2/IEEE754_2008.pdf
* ISO 4217 International Standard for currency codes: https://www.iso.org/iso-4217-currency-codes.html, https://en.wikipedia.org/wiki/ISO_4217
* ISO 3166 International Standard for country codes: https://www.iso.org/iso-3166-country-codes.html, https://en.wikipedia.org/wiki/ISO_3166

# Implementations
Intel Decimal Floating-Point Math Library (implementation of IEEE 754-2008): https://software.intel.com/en-us/articles/intel-decimal-floating-point-math-library

A C/C++ library for money and ISO 4217 currency codes: https://github.com/castedo/isomon, http://ref.castedo.com/isomon

Yet Another C++ Money class: http://www.di-mare.com/adolfo/p/money.htm

moneycpp: https://github.com/mariusbancila/moneycpp, https://mariusbancila.ro/blog/2018/11/13/moneycpp-a-cpp-library-for-handling-monetary-values/

Not sure what quantitative finance is, but here is a library for it: https://www.quantlib.org/

Also, it appears that the C++ standard added I/O Manipulation functions for money: https://en.cppreference.com/w/cpp/io/manip/get_money

A code review of a simple money class: https://codereview.stackexchange.com/questions/109821/simple-c-class-for-storing-and-manipulations-with-money

# Requirements
1. Can add or subtract money to/from money:
    1. money + money = money
    2. money - money = money
2. Cannot add or subtract money to/from numbers:
    1. money + number = ?
    2. money - number = ?
    3. number - money = ?
3. Can multiply money by number
    1. money * number = money
4. Cannot multiply money by money:
    1. money * money = ?

Given the formula for division:

Dividend = Quotient * Divisor + Remainder 

Therefore:

| Case | Dividend | Quotient | Divisor | Remainder | Valid |
| ---- | -------- | -------- | ------- | --------- | ----- |
| 1 | number | number | number | number | Yes (not addressed by this class) |
| 2 | money | number | number | number | No (1.1) |
| 3 | number | money | number | number | No (2.1) |
| 4 | money | money | number | number | No (2.1) |
| 5 | number | number | money | number | No (2.1) |
| 6 | money | number | money | number | No (2.1) |
| 7 | number | money | money | number | No (4.1) |
| 8 | money | money | money | number | No (4.1) |
| 9 | number | number | number | money | No (2.1) |
| 10 | money | number | number | money | No (2.1) |
| 11 | number | money | number | money | No (1.1) |
| 12 | money | money | number | money | Yes |
| 13 | number | number | money | money | No (1.1) |
| 14 | money | number | money | money | Yes |
| 15 | number | money | money | money | No (4.1) |
| 16 | money | money | money | money | No (4.1) |

Thus, valid equations are:

money = number * money + money, and

money = money * number + money

money / money = number (remainder: money)

money / number = money (remainder: money)

C++ interface:
```
money operator+(money, money)
money operator-(money, money)
money operator*(money, number)
money operator*(number, money)
money operator%(money, number)
money operator%(money, money)
money operator/(money, number)
number operator/(money, money)
```