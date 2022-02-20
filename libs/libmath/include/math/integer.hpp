// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_MATH_INTEGER_HPP
#define TYBL_MATH_INTEGER_HPP

#include <array>
#include <functional> // std::equal, std::lexicographical_compare
#include <iostream>   // TODO(tybl): Remove use of std::cerr
#include <limits>     // std::numeric_limits
#include <ostream>    // insertion operator
#include <string>

namespace tybl::math {

template <typename TYPE>
struct next_largest {};

template <>
struct next_largest<uint8_t> {
  using type = uint16_t;
};
template <>
struct next_largest<uint16_t> {
  using type = uint32_t;
};
template <>
struct next_largest<uint32_t> {
  using type = uint64_t;
};
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
  basic_unsigned_integer(intmax_t p_seed) = delete;
  basic_unsigned_integer(uintmax_t p_seed)
    : mantissa{} {
    for (size_t i = 0; i < size && 0 != p_seed; ++i) {
      mantissa[i] = p_seed & limb_mask;
      p_seed >>= binary_digits;
    }
  }
  basic_unsigned_integer(const std::string& p_seed)
    : mantissa{} {
    for (auto character : p_seed) {
      if (!isdigit(character)) {
        break;
      }
      operator*=(10).operator+=(static_cast<TYPE>(character - '0'));
    }
  }
  basic_unsigned_integer(const basic_unsigned_integer& p_other) {
    std::copy(p_other.mantissa.begin(), p_other.mantissa.end(), mantissa.begin());
  }
  auto operator=(basic_unsigned_integer p_other) -> basic_unsigned_integer& {
    std::swap(mantissa, p_other.mantissa);
    return *this;
  }
  auto operator+=(TYPE p_other) -> basic_unsigned_integer& {
    larger_uint carry = p_other;
    for (size_t i = 0; i < size && 0 != carry; ++i) {
      carry = add_at_index(i, carry);
    }
    if (0 != carry) {
      std::cerr << __LINE__ << ": carry: " << carry << std::endl;
    }
    return *this;
  }
  auto operator+=(const basic_unsigned_integer& p_other) -> basic_unsigned_integer& {
    larger_uint carry = 0;
    for (size_t i = 0; i < size; ++i) {
      carry = add_at_index(i, static_cast<larger_uint>(carry + p_other.mantissa[i]));
    }
    if (0 != carry) {
      std::cerr << __LINE__ << ": carry: " << carry << std::endl;
    }
    return *this;
  }
  auto operator-=(const basic_unsigned_integer& p_other) -> basic_unsigned_integer& {
    TYPE carry = 0;
    for (size_t i = 0; i < size; ++i) {
      TYPE temp = mantissa[i];
      bool underflow = (temp < carry);
      temp = static_cast<TYPE>(temp - carry);
      underflow |= (temp < p_other.mantissa[i]);
      mantissa[i] = static_cast<TYPE>(temp - p_other.mantissa[i]);
      carry = static_cast<TYPE>(underflow);
    }
    return *this;
  }
  auto operator*=(TYPE p_other) -> basic_unsigned_integer& {
    larger_uint carry = 0;
    for (size_t i = 0; i < size; ++i) {
      larger_uint overflow = multiply_at_index(i, p_other);
      if (0 != carry) {
        overflow = static_cast<larger_uint>(overflow + add_at_index(i, carry));
      }
      carry = overflow;
    }
    if (0 != carry) {
      std::cerr << __LINE__ << ": carry: " << carry << std::endl;
    }
    return *this;
  }
  auto operator*=(const basic_unsigned_integer& p_other) -> basic_unsigned_integer& {
    larger_uint carry = 0;
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size && (i + j) < size; ++j) {
        carry += multiply_at_index(i, p_other.mantissa[j]);
        carry = add_at_index(i, carry);
      }
    }
    if (0 != carry) {
      std::cerr << __LINE__ << ": carry: " << carry << std::endl;
    }
    return *this;
  }
  auto operator/=(const basic_unsigned_integer& /*other*/) -> basic_unsigned_integer& {
    // TODO(tybl): implement operator/=()
    throw std::bad_function_call();
    return *this;
  }
  auto operator++() -> basic_unsigned_integer& { return operator+=(1); }
  auto operator++(int) -> basic_unsigned_integer {
    basic_unsigned_integer<TYPE, size> temp(*this);
    operator+=(1);
    return temp;
  }
  auto operator>>=(size_t /*places*/) -> basic_unsigned_integer& {
    // TODO(tybl): implement operator>>=()
    throw std::bad_function_call();
    return *this;
  }
  auto operator<<=(size_t p_places) -> basic_unsigned_integer& {
    const size_t whole_shifts = p_places / binary_digits;
    const size_t limb_shift = p_places % binary_digits;
    const size_t overflow_shift = binary_digits - limb_shift;
    if (size <= whole_shifts) {
      std::fill(mantissa.begin(), mantissa.end(), 0);
      return *this;
    }
    if (0 < whole_shifts /* < size*/) {
      std::copy(mantissa.crbegin() + static_cast<std::ptrdiff_t>(whole_shifts), mantissa.crend(), mantissa.rbegin());
      std::fill(mantissa.begin(), mantissa.begin() + static_cast<std::ptrdiff_t>(whole_shifts), 0);
    }
    if (0 < limb_shift) {
      TYPE carry = 0;
      for (size_t i = whole_shifts; i < size; ++i) {
        TYPE temp = mantissa[i];
        TYPE overflow = static_cast<TYPE>(temp >> overflow_shift);
        mantissa[i] = static_cast<TYPE>((temp << limb_shift) | carry);
        carry = overflow;
      }
    }
    return *this;
  }
  auto operator==(const basic_unsigned_integer& p_other) const -> bool {
    return std::equal(mantissa.begin(), mantissa.end(), p_other.mantissa.begin());
  }
  auto operator!=(const basic_unsigned_integer& p_other) const -> bool { return !operator==(p_other); }
  auto operator<=(const basic_unsigned_integer& p_other) const -> bool { return !operator>(p_other); }
  auto operator>=(const basic_unsigned_integer& p_other) const -> bool { return !operator<(p_other); }
  auto operator<(const basic_unsigned_integer& p_other) const -> bool {
    return std::lexicographical_compare(mantissa.crbegin(), mantissa.crend(), p_other.mantissa.crbegin(),
                                        p_other.mantissa.crend());
  }
  auto operator>(const basic_unsigned_integer& p_other) const -> bool {
    return std::lexicographical_compare(mantissa.crbegin(), mantissa.crend(), p_other.mantissa.crbegin(),
                                        p_other.mantissa.crend(), std::greater<TYPE>());
  }

private:
  auto multiply_at_index(size_t p_index, larger_uint p_value) -> TYPE {
    auto result = static_cast<larger_uint>(p_value * mantissa[p_index]);
    mantissa[p_index] = static_cast<TYPE>(result & limb_mask);
    return static_cast<TYPE>(result >> binary_digits);
  }
  auto add_at_index(size_t p_index, larger_uint p_value) -> TYPE {
    auto result = static_cast<larger_uint>(p_value + mantissa[p_index]);
    mantissa[p_index] = static_cast<TYPE>(result & limb_mask);
    return static_cast<TYPE>(result >> binary_digits);
  }

public:
  std::array<TYPE, size> mantissa;
};

template <typename TYPE, size_t size>
auto operator<<(std::ostream& p_out, const basic_unsigned_integer<TYPE, size>& p_value) -> std::ostream& {
  p_out << std::hex;
  for (auto limb : p_value.mantissa) {
    p_out << static_cast<uint64_t>(limb) << " ";
  }
  return p_out;
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

#endif // TYBL_MATH_INTEGER_HPP
