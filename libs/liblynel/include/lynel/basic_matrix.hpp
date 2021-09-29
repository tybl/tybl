// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LYNEL_BASICMATRIX_HPP
#define TYBL_LYNEL_BASICMATRIX_HPP

#include "vodka/algorithm/max.hpp"
#include "vodka/algorithm/min.hpp"
#include "vodka/type_traits/enable_if.hpp"

#include <stddef.h> // size_t

namespace tybl::lynel {

constexpr bool is_vec(size_t extent, size_t rows, size_t cols) {
  return ((rows == extent) && (1 == cols)) || ((cols == extent) && (1 == rows));
}

constexpr bool is_mat(size_t extent, size_t rows, size_t cols) {
  return (cols == extent) && (1 < rows);
}

template <typename T, size_t R, size_t C, typename S = void> struct basic_matrix;

template <typename T> using cvec2 = basic_matrix<T,2,1>;
template <typename T> using rvec2 = basic_matrix<T,1,2>;
template <typename T> using cvec3 = basic_matrix<T,3,1>;
template <typename T> using rvec3 = basic_matrix<T,1,3>;
template <typename T> using cvec4 = basic_matrix<T,4,1>;
template <typename T> using rvec4 = basic_matrix<T,1,4>;

template <typename T> using mat2 = basic_matrix<T,2,2>;
template <typename T> using mat3 = basic_matrix<T,3,3>;
template <typename T> using mat4 = basic_matrix<T,4,4>;

template <typename T, size_t N> using smat = basic_matrix<T,N,N>;
template <typename T, size_t N> using cvec = basic_matrix<T,N,1>;
template <typename T, size_t N> using rvec = basic_matrix<T,1,N>;

// Rank 2 Vector specialization
template <typename T, size_t M, size_t N>
struct basic_matrix<T,M,N,typename vodka::enable_if_t<is_vec(2,M,N)>> {
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
struct basic_matrix<T,M,N, typename vodka::enable_if_t<is_vec(3,M,N)>> {
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
struct basic_matrix<T,M,N,typename vodka::enable_if_t<is_vec(4,M,N)>> {
  using value_type = T;
  value_type x, y, z, w;
  constexpr auto operator==(basic_matrix const& v) const -> bool { return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w); }
  constexpr auto operator+=(basic_matrix const& v) -> basic_matrix& { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
  constexpr auto operator-=(basic_matrix const& v) -> basic_matrix& { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
  constexpr auto operator*=(value_type s) -> basic_matrix& { x *= s; y *= s; z *= s; w *= s; return *this; }
  constexpr auto operator/=(value_type s) -> basic_matrix& { x /= s; y /= s; z /= s; w /= s; return *this; }
  constexpr auto dot(basic_matrix const& v) const -> value_type { return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w); }
};

// Rank 4 Column Vector specialization
template <typename T>
struct basic_matrix<T,1,1,void> {
  using value_type = T;
  value_type x;
  constexpr auto operator==(basic_matrix const& v) const -> bool { return (x == v.x); }
  constexpr auto operator+=(basic_matrix const& v) -> basic_matrix& { x += v.x; return *this; }
  constexpr auto operator-=(basic_matrix const& v) -> basic_matrix& { x -= v.x; return *this; }
  constexpr auto operator*=(value_type s) -> basic_matrix& { x *= s; return *this; }
  constexpr auto operator/=(value_type s) -> basic_matrix& { x /= s; return *this; }
  constexpr auto dot(basic_matrix const& v) const -> value_type { return (x * v.x); }
};

// Two column matrices
template <typename T, size_t M, size_t N>
struct basic_matrix<T,M,N,typename vodka::enable_if_t<is_mat(2,M,N)>> {
  using value_type = T;
  cvec<value_type,M> x,y;
  constexpr auto operator==(basic_matrix const& v) const -> bool { return (x == v.x) && (y == v.y); }
  constexpr auto operator+=(basic_matrix const& v) -> basic_matrix& { x += v.x; y += v.y; return *this; }
  constexpr auto operator-=(basic_matrix const& v) -> basic_matrix& { x -= v.x; y -= v.y; return *this; }
  constexpr auto operator*=(value_type s) -> basic_matrix& { x *= s; y *= s; return *this; }
  constexpr auto operator/=(value_type s) -> basic_matrix& { x /= s; y /= s; return *this; }
};

// Three column matrices
template <typename T, size_t M, size_t N>
struct basic_matrix<T,M,N,typename vodka::enable_if_t<is_mat(3,M,N)>> {
  using value_type = T;
  cvec<value_type,M> x,y,z;
  constexpr auto operator==(basic_matrix const& v) const -> bool { return (x == v.x) && (y == v.y) && (z == v.z); }
  constexpr auto operator+=(basic_matrix const& v) -> basic_matrix& { x += v.x; y += v.y; z += v.z; return *this; }
  constexpr auto operator-=(basic_matrix const& v) -> basic_matrix& { x -= v.x; y -= v.y; z -= v.z; return *this; }
  constexpr auto operator*=(value_type s) -> basic_matrix& { x *= s; y *= s; z *= s; return *this; }
  constexpr auto operator/=(value_type s) -> basic_matrix& { x /= s; y /= s; z /= s; return *this; }
};

// Three column matrices
template <typename T, size_t M, size_t N>
struct basic_matrix<T,M,N,typename vodka::enable_if_t<is_mat(4,M,N)>> {
  using value_type = T;
  cvec<value_type,M> x,y,z,w;
  constexpr auto operator==(basic_matrix const& v) const -> bool { return (x == v.x) && (y == v.y) && (z == v.z); }
  constexpr auto operator+=(basic_matrix const& v) -> basic_matrix& { x += v.x; y += v.y; z += v.z; return *this; }
  constexpr auto operator-=(basic_matrix const& v) -> basic_matrix& { x -= v.x; y -= v.y; z -= v.z; return *this; }
  constexpr auto operator*=(value_type s) -> basic_matrix& { x *= s; y *= s; z *= s; return *this; }
  constexpr auto operator/=(value_type s) -> basic_matrix& { x /= s; y /= s; z /= s; return *this; }
};

template <typename T, size_t M, size_t N> constexpr auto add(basic_matrix<T,M,N> l, basic_matrix<T,M,N> const& r) -> basic_matrix<T,M,N> { return l += r; }
template <typename T, size_t M, size_t N> constexpr auto sub(basic_matrix<T,M,N> l, basic_matrix<T,M,N> const& r) -> basic_matrix<T,M,N> { return l -= r; }
template <typename T, size_t M, size_t N> constexpr auto operator*(T s, basic_matrix<T,M,N> v) -> basic_matrix<T,M,N> { return v *= s; }

// Multiplication
//template <typename T, size_t N> using cvec = basic_matrix<T,N,1>;
template <typename T, size_t M> constexpr cvec<T,M> mul(basic_matrix<T,M,1> const& l, cvec<T,1> const& r) { return l.x*r.x; }
template <typename T, size_t M> constexpr cvec<T,M> mul(basic_matrix<T,M,2> const& l, cvec<T,2> const& r) { return l.x*r.x + l.y*r.y; }
template <typename T, size_t M> constexpr cvec<T,M> mul(basic_matrix<T,M,3> const& l, cvec<T,3> const& r) { return l.x*r.x + l.y*r.y + l.z*r.z; }
template <typename T, size_t M> constexpr cvec<T,M> mul(basic_matrix<T,M,4> const& l, cvec<T,4> const& r) { return l.x*r.x + l.y*r.y + l.z*r.z + l.w*r.w; }
template <typename T, size_t M, size_t N> constexpr basic_matrix<T,M,1> mul(basic_matrix<T,M,N> const& l, basic_matrix<T,N,1> const& r) { return {mul(l,static_cast<cvec<T,1>>(r.x))}; }
template <typename T, size_t M, size_t N> constexpr basic_matrix<T,M,2> mul(basic_matrix<T,M,N> const& l, basic_matrix<T,N,2> const& r) { return {mul(l,static_cast<cvec<T,1>>(r.x)), mul(l,static_cast<cvec<T,1>>(r.y))}; }
template <typename T, size_t M, size_t N> constexpr basic_matrix<T,M,3> mul(basic_matrix<T,M,N> const& l, basic_matrix<T,N,3> const& r) { return {mul(l,r.x), mul(l,r.y), mul(l,r.z)}; }
template <typename T, size_t M, size_t N> constexpr basic_matrix<T,M,4> mul(basic_matrix<T,M,N> const& l, basic_matrix<T,N,4> const& r) { return {mul(l,r.x), mul(l,r.y), mul(l,r.z), mul(l,r.w)}; }
/*
template <typename T>
constexpr auto mul(basic_matrix<T,2,1> const& l, basic_matrix<T,1,2> const& r) -> basic_matrix<T,2,2> {
  return basic_matrix<T,2,2>{ l.x*r.x, l.x*r.y, l.y*r.x, l.y*r.y };
}
template <typename T>
constexpr auto mul(basic_matrix<T,3,1> const& l, basic_matrix<T,1,3> const& r) -> basic_matrix<T,3,3> {
  return basic_matrix<T,3,3>{ l.x*r.x, l.x*r.y, l.x*r.z, l.y*r.x, l.y*r.y, l.y*r.z, l.z*r.x, l.z*r.y, l.z*r.z };
}
template <typename T>
constexpr auto mul(basic_matrix<T,4,1> const& l, basic_matrix<T,1,4> const& r) -> basic_matrix<T,4,4> {
  return basic_matrix<T,4,4>{ l.x*r.x, l.x*r.y, l.x*r.z, l.x*r.w, l.y*r.x, l.y*r.y, l.y*r.z, l.y*r.w, l.z*r.x, l.z*r.y, l.z*r.z, l.z*r.w, l.w*r.x, l.w*r.y, l.w*r.z, l.w*r.w };
}
*/

} // namespace tybl::lynel

#endif // TYBL_LYNEL_BASICMATRIX_HPP
