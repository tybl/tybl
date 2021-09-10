// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_BASICMATRIX_HPP
#define TYBL_LINAL_BASICMATRIX_HPP

#include "vodka/algorithm/max.hpp"
#include "vodka/algorithm/min.hpp"
#include "vodka/type_traits/enable_if.hpp"

#include <stddef.h> // size_t

namespace tybl::linal {

template <size_t Extent, size_t Rows, size_t Cols>
struct is_vec : vodka::bool_constant<vodka::max(Rows,Cols) == Extent && vodka::min(Rows,Cols) == 1> {};

template <typename T, size_t R, size_t C, typename S = void> struct basic_matrix;

// Rank 2 Vector specialization
template <typename T, size_t M, size_t N>
struct basic_matrix<T,M,N,typename vodka::enable_if_t<is_vec<2,M,N>::value>> {
  using value_type = T;
  value_type x,y;
  constexpr auto operator==(basic_matrix const& v) const -> bool { return (x == v.x) && (y == v.y); }
  constexpr auto operator+=(basic_matrix const& v) -> basic_matrix& { x += v.x; y += v.y; return *this; }
  constexpr auto operator-=(basic_matrix const& v) -> basic_matrix& { x -= v.x; y -= v.y; return *this; }
  constexpr auto operator*=(value_type s) -> basic_matrix& { x *= s; y *= s; return *this; }
  constexpr auto operator/=(value_type s) -> basic_matrix& { x /= s; y /= s; return *this; }
  constexpr auto dot(basic_matrix const& v) const -> value_type { return (x * v.x) + (y * v.y); }
};

// Rank 3 Column Vector specialization
template <typename T, size_t M, size_t N>
struct basic_matrix<T,M,N, typename vodka::enable_if_t<is_vec<3,M,N>::value>> {
  using value_type = T;
  value_type x, y, z;
  constexpr auto operator==(basic_matrix const& v) const -> bool { return (x == v.x) && (y == v.y) && (z == v.z); }
  constexpr auto operator+=(basic_matrix const& v) -> basic_matrix& { x += v.x; y += v.y; z += v.z; return *this; }
  constexpr auto operator-=(basic_matrix const& v) -> basic_matrix& { x -= v.x; y -= v.y; z -= v.z; return *this; }
  constexpr auto operator*=(value_type s) -> basic_matrix& { x *= s; y *= s; z *= s; return *this; }
  constexpr auto operator/=(value_type s) -> basic_matrix& { x /= s; y /= s; z /= s; return *this; }
  constexpr auto dot  (basic_matrix const& v) const -> value_type { return (x * v.x) + (y * v.y) + (z * v.z); }
  constexpr auto cross(basic_matrix const& v) const -> basic_matrix { return basic_matrix{ (y*v.z)-(z*v.y),(z*v.x)-(x*v.z),(x*v.y)-(y*v.x) }; }
};

// Rank 4 Column Vector specialization
template <typename T, size_t M, size_t N>
struct basic_matrix<T,M,N,typename vodka::enable_if_t<is_vec<4,M,N>::value>> {
  using value_type = T;
  value_type x, y, z, w;
  constexpr auto operator==(basic_matrix const& v) const -> bool { return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w); }
  constexpr auto operator+=(basic_matrix const& v) -> basic_matrix& { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
  constexpr auto operator-=(basic_matrix const& v) -> basic_matrix& { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
  constexpr auto operator*=(value_type s) -> basic_matrix& { x *= s; y *= s; z *= s; w *= s; return *this; }
  constexpr auto operator/=(value_type s) -> basic_matrix& { x /= s; y /= s; z /= s; w /= s; return *this; }
  constexpr auto dot(basic_matrix const& v) const -> value_type { return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w); }
};

template <typename T, size_t M, size_t N> constexpr auto add(basic_matrix<T,M,N> l, basic_matrix<T,M,N> const& r) -> basic_matrix<T,M,N> { return l += r; }
template <typename T, size_t M, size_t N> constexpr auto sub(basic_matrix<T,M,N> l, basic_matrix<T,M,N> const& r) -> basic_matrix<T,M,N> { return l -= r; }
template <typename T, size_t M, size_t N> constexpr auto operator*(T s, basic_matrix<T,M,N> v) -> basic_matrix<T,M,N> { return v *= s; }

template <typename T> using mat2 = basic_matrix<T,2,2>;
template <typename T> using mat3 = basic_matrix<T,3,3>;
template <typename T> using mat4 = basic_matrix<T,4,4>;

template <typename T> using cvec2 = basic_matrix<T,2,1>;
template <typename T> using rvec2 = basic_matrix<T,1,2>;
template <typename T> using cvec3 = basic_matrix<T,3,1>;
template <typename T> using rvec3 = basic_matrix<T,1,3>;
template <typename T> using cvec4 = basic_matrix<T,4,1>;
template <typename T> using rvec4 = basic_matrix<T,1,4>;

template <typename T, size_t N> using smatrix = basic_matrix<T,N,N>;
template <typename T, size_t N> using cvector = basic_matrix<T,N,1>;
template <typename T, size_t N> using rvector = basic_matrix<T,1,N>;

} // namespace tybl::linal

#endif // TYBL_LINAL_BASICMATRIX_HPP
