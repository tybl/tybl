// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LYNEL_BASICMATRIX_HPP
#define TYBL_LYNEL_BASICMATRIX_HPP

#include <cstddef> // size_t
#include <type_traits>

namespace tybl::lynel {

constexpr auto is_vec(size_t p_extent, size_t p_rows, size_t p_cols) -> bool {
  return ((p_rows == p_extent) && (1 == p_cols)) || ((p_cols == p_extent) && (1 == p_rows));
}

constexpr auto is_mat(size_t p_extent, size_t p_rows, size_t p_cols) -> bool { return (p_cols == p_extent) && (1 < p_rows); }

template <typename T, size_t R, size_t C, typename S = void>
struct basic_matrix;

template <typename T>
using cvec2 = basic_matrix<T, 2, 1>;
template <typename T>
using rvec2 = basic_matrix<T, 1, 2>;
template <typename T>
using cvec3 = basic_matrix<T, 3, 1>;
template <typename T>
using rvec3 = basic_matrix<T, 1, 3>;
template <typename T>
using cvec4 = basic_matrix<T, 4, 1>;
template <typename T>
using rvec4 = basic_matrix<T, 1, 4>;

template <typename T>
using mat2 = basic_matrix<T, 2, 2>;
template <typename T>
using mat3 = basic_matrix<T, 3, 3>;
template <typename T>
using mat4 = basic_matrix<T, 4, 4>;

template <typename T, size_t N>
using smat = basic_matrix<T, N, N>;
template <typename T, size_t N>
using cvec = basic_matrix<T, N, 1>;
template <typename T, size_t N>
using rvec = basic_matrix<T, 1, N>;

// Rank 2 Vector specialization
template <typename T, size_t M, size_t N>
struct basic_matrix<T, M, N, typename std::enable_if_t<is_vec(2, M, N)>> {
  using value_type = T;
  value_type x, y;
  constexpr auto operator==(basic_matrix const& p_v) const -> bool { return (x == p_v.x) && (y == p_v.y); }
  constexpr auto operator+=(basic_matrix const& p_v) -> basic_matrix& {
    x += p_v.x;
    y += p_v.y;
    return *this;
  }
  constexpr auto operator-=(basic_matrix const& p_v) -> basic_matrix& {
    x -= p_v.x;
    y -= p_v.y;
    return *this;
  }
  constexpr auto operator*=(value_type p_s) -> basic_matrix& {
    x *= p_s;
    y *= p_s;
    return *this;
  }
  constexpr auto operator/=(value_type p_s) -> basic_matrix& {
    x /= p_s;
    y /= p_s;
    return *this;
  }
  [[nodiscard]] constexpr auto dot(basic_matrix const& p_v) const -> value_type { return (x * p_v.x) + (y * p_v.y); }
};

// Rank 3 Column Vector specialization
template <typename T, size_t M, size_t N>
struct basic_matrix<T, M, N, typename std::enable_if_t<is_vec(3, M, N)>> {
  using value_type = T;
  value_type x, y, z;
  constexpr auto operator==(basic_matrix const& p_v) const -> bool {
    return (x == p_v.x) && (y == p_v.y) && (z == p_v.z);
  }
  constexpr auto operator+=(basic_matrix const& p_v) -> basic_matrix& {
    x += p_v.x;
    y += p_v.y;
    z += p_v.z;
    return *this;
  }
  constexpr auto operator-=(basic_matrix const& p_v) -> basic_matrix& {
    x -= p_v.x;
    y -= p_v.y;
    z -= p_v.z;
    return *this;
  }
  constexpr auto operator*=(value_type p_s) -> basic_matrix& {
    x *= p_s;
    y *= p_s;
    z *= p_s;
    return *this;
  }
  constexpr auto operator/=(value_type p_s) -> basic_matrix& {
    x /= p_s;
    y /= p_s;
    z /= p_s;
    return *this;
  }
  [[nodiscard]] constexpr auto dot(basic_matrix const& p_v) const -> value_type { return (x * p_v.x) + (y * p_v.y) + (z * p_v.z); }
  [[nodiscard]] constexpr auto cross(basic_matrix const& p_v) const -> basic_matrix {
    return basic_matrix{(y * p_v.z) - (z * p_v.y), (z * p_v.x) - (x * p_v.z), (x * p_v.y) - (y * p_v.x)};
  }
};

// Rank 4 Column Vector specialization
template <typename T, size_t M, size_t N>
struct basic_matrix<T, M, N, typename std::enable_if_t<is_vec(4, M, N)>> {
  using value_type = T;
  value_type x, y, z, w;
  constexpr auto operator==(basic_matrix const& p_v) const -> bool {
    return (x == p_v.x) && (y == p_v.y) && (z == p_v.z) && (w == p_v.w);
  }
  constexpr auto operator+=(basic_matrix const& p_v) -> basic_matrix& {
    x += p_v.x;
    y += p_v.y;
    z += p_v.z;
    w += p_v.w;
    return *this;
  }
  constexpr auto operator-=(basic_matrix const& p_v) -> basic_matrix& {
    x -= p_v.x;
    y -= p_v.y;
    z -= p_v.z;
    w -= p_v.w;
    return *this;
  }
  constexpr auto operator*=(value_type p_s) -> basic_matrix& {
    x *= p_s;
    y *= p_s;
    z *= p_s;
    w *= p_s;
    return *this;
  }
  constexpr auto operator/=(value_type p_s) -> basic_matrix& {
    x /= p_s;
    y /= p_s;
    z /= p_s;
    w /= p_s;
    return *this;
  }
  [[nodiscard]] constexpr auto dot(basic_matrix const& p_v) const -> value_type {
    return (x * p_v.x) + (y * p_v.y) + (z * p_v.z) + (w * p_v.w);
  }
};

// Rank 4 Column Vector specialization
template <typename T>
struct basic_matrix<T, 1, 1, void> {
  using value_type = T;
  value_type x;
  constexpr auto operator==(basic_matrix const& p_v) const -> bool { return (x == p_v.x); }
  constexpr auto operator+=(basic_matrix const& p_v) -> basic_matrix& {
    x += p_v.x;
    return *this;
  }
  constexpr auto operator-=(basic_matrix const& p_v) -> basic_matrix& {
    x -= p_v.x;
    return *this;
  }
  constexpr auto operator*=(value_type p_s) -> basic_matrix& {
    x *= p_s;
    return *this;
  }
  constexpr auto operator/=(value_type p_s) -> basic_matrix& {
    x /= p_s;
    return *this;
  }
  constexpr auto dot(basic_matrix const& p_v) const -> value_type { return (x * p_v.x); }
};

// Two column matrices
template <typename T, size_t M, size_t N>
struct basic_matrix<T, M, N, typename std::enable_if_t<is_mat(2, M, N)>> {
  using value_type = T;
  cvec<value_type, M> x, y;
  constexpr auto operator==(basic_matrix const& p_v) const -> bool { return (x == p_v.x) && (y == p_v.y); }
  constexpr auto operator+=(basic_matrix const& p_v) -> basic_matrix& {
    x += p_v.x;
    y += p_v.y;
    return *this;
  }
  constexpr auto operator-=(basic_matrix const& p_v) -> basic_matrix& {
    x -= p_v.x;
    y -= p_v.y;
    return *this;
  }
  constexpr auto operator*=(value_type p_s) -> basic_matrix& {
    x *= p_s;
    y *= p_s;
    return *this;
  }
  constexpr auto operator/=(value_type p_s) -> basic_matrix& {
    x /= p_s;
    y /= p_s;
    return *this;
  }
};

// Three column matrices
template <typename T, size_t M, size_t N>
struct basic_matrix<T, M, N, typename std::enable_if_t<is_mat(3, M, N)>> {
  using value_type = T;
  cvec<value_type, M> x, y, z;
  constexpr auto operator==(basic_matrix const& p_v) const -> bool {
    return (x == p_v.x) && (y == p_v.y) && (z == p_v.z);
  }
  constexpr auto operator+=(basic_matrix const& p_v) -> basic_matrix& {
    x += p_v.x;
    y += p_v.y;
    z += p_v.z;
    return *this;
  }
  constexpr auto operator-=(basic_matrix const& p_v) -> basic_matrix& {
    x -= p_v.x;
    y -= p_v.y;
    z -= p_v.z;
    return *this;
  }
  constexpr auto operator*=(value_type p_s) -> basic_matrix& {
    x *= p_s;
    y *= p_s;
    z *= p_s;
    return *this;
  }
  constexpr auto operator/=(value_type p_s) -> basic_matrix& {
    x /= p_s;
    y /= p_s;
    z /= p_s;
    return *this;
  }
};

// Three column matrices
template <typename T, size_t M, size_t N>
struct basic_matrix<T, M, N, typename std::enable_if_t<is_mat(4, M, N)>> {
  using value_type = T;
  cvec<value_type, M> x, y, z, w;
  constexpr auto operator==(basic_matrix const& p_v) const -> bool {
    return (x == p_v.x) && (y == p_v.y) && (z == p_v.z);
  }
  constexpr auto operator+=(basic_matrix const& p_v) -> basic_matrix& {
    x += p_v.x;
    y += p_v.y;
    z += p_v.z;
    return *this;
  }
  constexpr auto operator-=(basic_matrix const& p_v) -> basic_matrix& {
    x -= p_v.x;
    y -= p_v.y;
    z -= p_v.z;
    return *this;
  }
  constexpr auto operator*=(value_type p_s) -> basic_matrix& {
    x *= p_s;
    y *= p_s;
    z *= p_s;
    return *this;
  }
  constexpr auto operator/=(value_type p_s) -> basic_matrix& {
    x /= p_s;
    y /= p_s;
    z /= p_s;
    return *this;
  }
};

template <typename T, size_t M, size_t N>
constexpr auto operator+(basic_matrix<T, M, N> p_lhs, basic_matrix<T, M, N> const& p_rhs) -> basic_matrix<T, M, N> {
  return p_lhs += p_rhs;
}
template <typename T, size_t M, size_t N>
constexpr auto operator-(basic_matrix<T, M, N> p_lhs, basic_matrix<T, M, N> const& p_rhs) -> basic_matrix<T, M, N> {
  return p_lhs -= p_rhs;
}

// Multiplication
template <typename T, size_t M, size_t N>
constexpr auto operator*(T p_s, basic_matrix<T, M, N> p_v) -> basic_matrix<T, M, N> {
  return p_v *= p_s;
}
template <typename T, size_t M, size_t N>
constexpr auto operator*(basic_matrix<T, M, N> p_v, T p_s) -> basic_matrix<T, M, N> {
  return p_v *= p_s;
}
template <typename T, size_t M>
constexpr auto operator*(basic_matrix<T, M, 1> const& p_lhs, cvec<T, 1> const& p_rhs) -> cvec<T, M> {
  return p_lhs * p_rhs.x;
}
template <typename T, size_t M>
constexpr auto operator*(basic_matrix<T, M, 2> const& p_lhs, cvec<T, 2> const& p_rhs) -> cvec<T, M> {
  return p_lhs.x * p_rhs.x + p_lhs.y * p_rhs.y;
}
template <typename T, size_t M>
constexpr auto operator*(basic_matrix<T, M, 3> const& p_lhs, cvec<T, 3> const& p_rhs) -> cvec<T, M> {
  return p_lhs.x * p_rhs.x + p_lhs.y * p_rhs.y + p_lhs.z * p_rhs.z;
}
template <typename T, size_t M>
constexpr auto operator*(basic_matrix<T, M, 4> const& p_lhs, cvec<T, 4> const& p_rhs) -> cvec<T, M> {
  return p_lhs.x * p_rhs.x + p_lhs.y * p_rhs.y + p_lhs.z * p_rhs.z + p_lhs.w * p_rhs.w;
}
template <typename T, size_t M, size_t N>
constexpr auto operator*(basic_matrix<T, M, N> const& p_lhs, basic_matrix<T, N, 2> const& p_rhs)
    -> basic_matrix<T, M, 2> {
  return {p_lhs * p_rhs.x, p_lhs * p_rhs.y};
}
template <typename T, size_t M, size_t N>
constexpr auto operator*(basic_matrix<T, M, N> const& p_lhs, basic_matrix<T, N, 3> const& p_rhs)
    -> basic_matrix<T, M, 3> {
  return {p_lhs * p_rhs.x, p_lhs * p_rhs.y, p_lhs * p_rhs.z};
}
template <typename T, size_t M, size_t N>
constexpr auto operator*(basic_matrix<T, M, N> const& p_lhs, basic_matrix<T, N, 4> const& p_rhs)
    -> basic_matrix<T, M, 4> {
  return {p_lhs * p_rhs.x, p_lhs * p_rhs.y, p_lhs * p_rhs.z, p_lhs * p_rhs.w};
}

} // namespace tybl::lynel

#endif // TYBL_LYNEL_BASICMATRIX_HPP
