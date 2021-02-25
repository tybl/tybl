// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_CSTDDEF_BYTE_HPP
#define TYBL_VODKA_CSTDDEF_BYTE_HPP

namespace tybl::vodka {

enum class byte
  : unsigned char {};

template <bool>
struct __enable_if_integral_imp {};

template <>
struct __enable_if_integral_imp<true> {
  using type = byte;
};

template <class _Tp>
using _EnableByteOverload = typename __enable_if_integral_imp<__libcpp_is_integral<_Tp>::value>::type;

[[nodiscard]]
constexpr auto
operator|(byte lhs, byte rhs) noexcept -> byte {
  return static_cast<byte>(
    static_cast<unsigned char>(
       static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
  ));
}

constexpr auto
operator|=(byte& lhs, byte rhs) noexcept -> byte& {
  return lhs = lhs | rhs;
}

[[nodiscard]]
constexpr auto
operator&(byte lhs, byte rhs) noexcept -> byte {
  return static_cast<byte>(
    static_cast<unsigned char>(
       static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs)
  ));
}

constexpr auto
operator&=(byte& lhs, byte rhs) noexcept -> byte& {
  return lhs = lhs & rhs;
}

[[nodiscard]]
constexpr auto
operator^(byte lhs, byte rhs) noexcept -> byte {
  return static_cast<byte>(
    static_cast<unsigned char>(
       static_cast<unsigned int>(lhs) ^ static_cast<unsigned int>(rhs)
  ));
}

constexpr auto
operator^=(byte& lhs, byte rhs) noexcept -> byte& {
  return lhs = lhs ^ rhs;
}

[[nodiscard]]
constexpr auto
operator~ (byte b) noexcept -> byte {
  return static_cast<byte>(
    static_cast<unsigned char>(
      ~static_cast<unsigned int>(b)
  ));
}

template <class _Integer>
[[nodiscard]] constexpr _EnableByteOverload<_Integer>
  operator<< (byte  __lhs, _Integer __shift) noexcept
  { return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(__lhs) << __shift)); }

template <class _Integer>
  constexpr _EnableByteOverload<_Integer> &
  operator<<=(byte& __lhs, _Integer __shift) noexcept
  { return __lhs = __lhs << __shift; }

template <class _Integer>
[[nodiscard]] constexpr _EnableByteOverload<_Integer>
  operator>> (byte  __lhs, _Integer __shift) noexcept
  { return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(__lhs) >> __shift)); }

template <class _Integer>
  constexpr _EnableByteOverload<_Integer> &
  operator>>=(byte& __lhs, _Integer __shift) noexcept
  { return __lhs = __lhs >> __shift; }

template <class _Integer, class = _EnableByteOverload<_Integer>>
[[nodiscard]] constexpr auto
to_integer(byte b) noexcept -> _Integer {
  return static_cast<_Integer>(b);
}

} // namespace tybl::vodka

#define TYBL_VODKA_CSTDDEF_BYTE_HPP
