// License: The Unlicense (https://unlicense.org)
#ifndef TBL_INTEGER_HPP
#define TBL_INTEGER_HPP

#include <array>
#include <functional> // std::equal, std::lexicographical_compare
#include <iostream> // TODO(tblyons): Remove use of std::cerr
#include <limits> // std::numeric_limits
#include <ostream> // insertion operator
#include <string>

namespace tybl::math {

template <typename TYPE>
struct next_largest { };

template <> struct next_largest<uint8_t> { using type = uint16_t; };
template <> struct next_largest<uint16_t> { using type = uint32_t; };
template <> struct next_largest<uint32_t> { using type = uint64_t; };
#if 0
template <> struct next_largest<uint64_t> { using type = unsigned __int128; };
#endif

template <typename TYPE, size_t size>
struct basic_unsigned_integer {
   static_assert(std::is_unsigned<TYPE>::value, "basic_unsigned_integer must be instantiated with an unsigned type");
   static_assert(0 < size, "basic_unsigned_integer must be instantiated with a non-zero number of limbs");

   using larger_uint = typename next_largest<TYPE>::type;
   static constexpr size_t binary_digits = std::numeric_limits<TYPE>::digits;
   static constexpr TYPE limb_mask = std::numeric_limits<TYPE>::max();

   basic_unsigned_integer() = default;
   basic_unsigned_integer(intmax_t seed) = delete;
   basic_unsigned_integer(uintmax_t seed)
      : mantissa{}
   {
      for (size_t i = 0; i < size && 0 != seed; ++i) {
         mantissa[i] = seed & limb_mask;
         seed >>= binary_digits;
      }
   }
   basic_unsigned_integer(const std::string& seed)
      : mantissa{}
   {
      for (auto character : seed) {
         if (!isdigit(character)) { break; }
         operator*=(10).operator+=(static_cast<TYPE>(character - '0'));
      }
   }
   basic_unsigned_integer(const basic_unsigned_integer& other) {
      std::copy(other.mantissa.begin(), other.mantissa.end(), mantissa.begin());
   }
   basic_unsigned_integer& operator=(basic_unsigned_integer other) {
      std::swap(mantissa, other.mantissa);
      return *this;
   }
   basic_unsigned_integer& operator+=(TYPE other) {
      larger_uint carry = other;
      for (size_t i = 0; i < size && 0 != carry; ++i) {
         carry = add_at_index(i, carry);
      }
      if (0 != carry) std::cerr << __LINE__ << ": carry: " << carry << std::endl;
      return *this;
   }
   basic_unsigned_integer& operator+=(const basic_unsigned_integer& other) {
      larger_uint carry = 0;
      for (size_t i = 0; i < size; ++i) {
         carry = add_at_index(i, carry + other.mantissa[i]);
      }
      if (0 != carry) std::cerr << __LINE__ << ": carry: " << carry << std::endl;
      return *this;
   }
   basic_unsigned_integer& operator-=(const basic_unsigned_integer& other) {
      TYPE carry = 0;
      for (size_t i = 0; i < size; ++i) {
         TYPE temp = mantissa[i];
         bool underflow = (temp < carry);
         temp -= carry;
         underflow |= (temp < other.mantissa[i]);
         mantissa[i] = temp - other.mantissa[i];
         carry = static_cast<TYPE>(underflow);
      }
      return *this;
   }
   basic_unsigned_integer& operator*=(TYPE other) {
      larger_uint carry = 0;
      for (size_t i = 0; i < size; ++i) {
         larger_uint overflow = multiply_at_index(i, other);
         if (0 != carry) {
            overflow += add_at_index(i, carry);
         }
         carry = overflow;
      }
      if (0 != carry) std::cerr << __LINE__ << ": carry: " << carry << std::endl;
      return *this;
   }
   basic_unsigned_integer& operator*=(const basic_unsigned_integer& other) {
      larger_uint carry = 0;
      for (size_t i = 0; i < size; ++i) {
         for (size_t j = 0; j < size && (i + j) < size; ++j) {
            carry += multiply_at_index(i, other.mantissa[j]);
            carry = add_at_index(i, carry);
         }
      }
      if (0 != carry) std::cerr << __LINE__ << ": carry: " << carry << std::endl;
      return *this;
   }
   basic_unsigned_integer& operator/=(const basic_unsigned_integer& /*other*/) {
      // TODO(tblyons): implement operator/=()
      throw std::bad_function_call();
      return *this;
   }
   basic_unsigned_integer& operator++() {
      return operator+=(1);
   }
   basic_unsigned_integer operator++(int) {
      basic_unsigned_integer<TYPE, size> temp(*this);
      operator+=(1);
      return temp;
   }
   basic_unsigned_integer& operator>>=(size_t /*places*/) {
      // TODO(tblyons): implement operator>>=()
      throw std::bad_function_call();
      return *this;
   }
   basic_unsigned_integer& operator<<=(size_t places) {
      const size_t whole_shifts = places / binary_digits;
      const size_t limb_shift = places % binary_digits;
      const size_t overflow_shift = binary_digits - limb_shift;
      if (size <= whole_shifts) {
         std::fill(mantissa.begin(), mantissa.end(), 0);
         return *this;
      } else if (0 < whole_shifts/* < size*/) {
         std::copy(mantissa.crbegin() + static_cast<std::ptrdiff_t>(whole_shifts), mantissa.crend(), mantissa.rbegin());
         std::fill(mantissa.begin(), mantissa.begin() + static_cast<std::ptrdiff_t>(whole_shifts), 0);
      }
      if (0 < limb_shift) {
         TYPE carry = 0;
         for (size_t i = whole_shifts; i < size; ++i) {
            TYPE temp = mantissa[i];
            TYPE overflow = temp >> overflow_shift;
            mantissa[i] = static_cast<TYPE>((temp << limb_shift) | carry);
            carry = overflow;
         }
      }
      return *this;
   }
   bool operator==(const basic_unsigned_integer& other) const {
      return std::equal(mantissa.begin(), mantissa.end(), other.mantissa.begin());
   }
   bool operator!=(const basic_unsigned_integer& other) const {
      return !operator==(other);
   }
   bool operator<=(const basic_unsigned_integer& other) const {
      return !operator>(other);
   }
   bool operator>=(const basic_unsigned_integer& other) const {
      return !operator<(other);
   }
   bool operator<(const basic_unsigned_integer& other) const {
      return std::lexicographical_compare(mantissa.crbegin(),
                                          mantissa.crend(),
                                          other.mantissa.crbegin(),
                                          other.mantissa.crend());
   }
   bool operator>(const basic_unsigned_integer& other) const {
      return std::lexicographical_compare(mantissa.crbegin(),
                                          mantissa.crend(),
                                          other.mantissa.crbegin(),
                                          other.mantissa.crend(),
                                          std::greater<TYPE>());
   }
private:
   TYPE multiply_at_index(size_t index, larger_uint value) {
      larger_uint result = value * mantissa[index];
      mantissa[index] = result & limb_mask;
      return result >> binary_digits;
   }
   TYPE add_at_index(size_t index, larger_uint value) {
      larger_uint result = value + mantissa[index];
      mantissa[index] = result & limb_mask;
      return result >> binary_digits;
   }
public:
   std::array<TYPE, size> mantissa;
};

template <typename TYPE, size_t size>
std::ostream& operator<<(std::ostream& out, const basic_unsigned_integer<TYPE, size>& value) {
   out << std::hex;
   for (auto limb : value.mantissa) {
      out << static_cast<uint64_t>(limb) << " ";
   }
   return out;
}

using uint24 = tybl::math::basic_unsigned_integer<uint8_t, 3>;
using uint32 = tybl::math::basic_unsigned_integer<uint8_t, 4>;
using uint40 = tybl::math::basic_unsigned_integer<uint8_t, 5>;
using uint48 = tybl::math::basic_unsigned_integer<uint16_t, 3>;
using uint56 = tybl::math::basic_unsigned_integer<uint8_t, 7>;
using uint96 = tybl::math::basic_unsigned_integer<uint32_t, 3>;
#if 0
using uint128 = tybl::math::basic_unsigned_integer<uint64_t, 2>;
using uint256 = tybl::math::basic_unsigned_integer<uint64_t, 4>;
using uint512 = tybl::math::basic_unsigned_integer<uint64_t, 8>;
#else
using uint128 = tybl::math::basic_unsigned_integer<uint32_t, 4>;
using uint256 = tybl::math::basic_unsigned_integer<uint32_t, 8>;
using uint512 = tybl::math::basic_unsigned_integer<uint32_t, 16>;
#endif

} // namespace tybl::math

static_assert(sizeof(tybl::math::uint24) == 3, "uint24_t is not 24bits long");
static_assert(sizeof(tybl::math::uint32) == 4, "uint24_t is not 24bits long");
static_assert(sizeof(tybl::math::uint40) == 5, "uint40_t is not 40bits long");
static_assert(sizeof(tybl::math::uint48) == 6, "uint48_t is not 48bits long");
static_assert(sizeof(tybl::math::uint56) == 7, "uint56_t is not 56bits long");
static_assert(sizeof(tybl::math::uint96) == 12, "uint96_t is not 96bits long");
static_assert(sizeof(tybl::math::uint128) == 16, "uint128_t is not 128bits long");
static_assert(sizeof(tybl::math::uint256) == 32, "uint256_t is not 256bits long");
static_assert(sizeof(tybl::math::uint512) == 64, "uint512_t is not 512bits long");

#endif // TBL_INTEGER_HPP
