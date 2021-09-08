// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LINAL_BASICMATRIX_HPP
#define TYBL_LINAL_BASICMATRIX_HPP

#include <stddef.h> // size_t

namespace tybl::linal {

template <typename T, size_t R, size_t C> struct basic_matrix;

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
