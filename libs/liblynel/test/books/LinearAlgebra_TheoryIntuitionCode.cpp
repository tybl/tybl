// License: The Unlicense (https://unlicense.org)
#include "lynel/basic_matrix.hpp"

#include <doctest/doctest.h>

#include <cmath> // M_PI
#include <type_traits>

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 23") {
  // These practice problems are symbolic manipulations and don't exercise
  // this library.
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 29") {
  using tybl::lynel::cvec2;
  using tybl::lynel::cvec4;
  using tybl::lynel::rvec2;
  using tybl::lynel::rvec4;

  // A
  cvec4<int> a = {1, 2, 3, 1};

  // B
  rvec4<int> b = {1, 2, 3, 1};
  CHECK(!std::is_same<decltype(a), decltype(b)>::value);

  // C
  cvec2<double> c = {-1, M_PI};

  // D
  rvec2<double> d = {7, 1.0 / 3.0};
  CHECK(!std::is_same<decltype(c), decltype(d)>::value);
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 33") { // NOLINT
  using tybl::lynel::cvec2;
  using tybl::lynel::cvec3;
  using tybl::lynel::rvec4;

  // A
  rvec4<double> a_in0 = {4, 5, 1, 0};
  rvec4<double> a_in1 = {-4, -3, 3, 10};
  rvec4<double> a_ans = {0, 2, 4, 10};
  auto a_result = a_in0 + a_in1;
  CHECK(a_ans == a_result);

  // B
  cvec3<double> b_in0 = {4, 2, 0};
  cvec3<double> b_in1 = {6, -4, 60};
  cvec3<double> b_in2 = {2, -5, 40};
  cvec3<double> b_ans = {0, 1, -20};
  auto b_result = b_in0 - b_in1 + b_in2;
  CHECK(b_ans == b_result);

  // C
  cvec2<double> c_in0 = {1, 0};
  cvec2<double> c_in1 = {1, 2};
  cvec2<double> c_ans = {2, 2};
  auto c_result = c_in0 + c_in1;
  CHECK(c_ans == c_result);

  // D
  cvec2<double> d_in0 = {2, 2};
  cvec2<double> d_in1 = {3, 4};
  cvec2<double> d_ans = {-1, -2};
  auto d_result = d_in0 - d_in1;
  CHECK(d_ans == d_result);

  // E
  cvec2<double> e_in0 = {-3, 1};
  cvec2<double> e_in1 = {3, -1};
  cvec2<double> e_ans = {0, 0};
  auto e_result = e_in0 + e_in1;
  CHECK(e_ans == e_result);

  // F
  cvec2<double> f_in0 = {1, 4};
  cvec2<double> f_in1 = {2, 8};
  cvec2<double> f_ans = {3, 12};
  auto f_result = f_in0 + f_in1;
  CHECK(f_ans == f_result);
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 36") {
  using tybl::lynel::cvec3;
  using tybl::lynel::cvec4;
  using tybl::lynel::rvec3;

  // A
  rvec3<double> a_in0 = {4, 3, 0};
  rvec3<double> a_ans = {-8, -6, 0};
  auto a_result = -2.0 * a_in0;
  CHECK(a_ans == a_result);

  // B
  cvec3<double> b_in0 = {0, 4, 3};
  cvec3<double> b_ans = {0, 4, 3};
  auto b_result = (-9.0 + 2.0 * 5.0) * b_in0;
  CHECK(b_ans == b_result);

  // C
  cvec4<double> c_in0 = {3, 3.14, 9, -234987234};
  cvec4<double> c_ans = {0, 0, 0, 0};
  auto c_result = 0.0 * c_in0;
  CHECK(c_ans == c_result);

  // D (symbol algebra not implemented)
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 50") { // NOLINT
  using tybl::lynel::cvec2;
  using tybl::lynel::cvec3;

  // A
  cvec2<int> a_in0 = {-4, -2};
  cvec2<int> a_in1 = {1, 3};
  int a_ans = -10;
  auto a_result = a_in0.dot(a_in1);
  CHECK(a_ans == a_result);

  // B
  cvec2<int> b_in0 = {2, 3};
  cvec2<int> b_in1 = {2, -3};
  int b_ans = -5;
  auto b_result = b_in0.dot(b_in1);
  CHECK(b_ans == b_result);

  // C
  cvec2<int> c_in0 = {7, -2};
  cvec2<int> c_in1 = {-7, -24};
  int c_ans = -1;
  auto c_result = c_in0.dot(c_in1);
  CHECK(c_ans == c_result);

  // D
  cvec2<double> d_in0 = {3.0 / 2.0, 4.0 / 5.0};
  cvec2<double> d_in1 = {2.0 / 3.0, -5.0 / 4.0};
  double d_ans = 0;
  auto d_result = d_in0.dot(d_in1);
  CHECK(d_ans == d_result);

  // E
  cvec3<int> e_in0 = {0, 1, 2};
  cvec3<int> e_in1 = {-2, -1, 0};
  int e_ans = -1;
  auto e_result = e_in0.dot(e_in1);
  CHECK(e_ans == e_result);

  // F
  cvec3<int> f_in0 = {4, 1, 3};
  cvec3<int> f_in1 = {4, 1, 3};
  int f_ans = 26;
  auto f_result = f_in0.dot(f_in1);
  CHECK(f_ans == f_result);

  // G
  cvec3<double> g_in0 = {7.0 / 2.0, -3.0, 6.0};
  cvec3<double> g_in1 = {10, 3.5, -4};
  double g_ans = 0.5;
  auto g_result = g_in0.dot(g_in1);
  CHECK(g_ans == g_result);

  // H
  cvec3<double> h_in0 = {81, 3, 9};
  cvec3<double> h_in1 = {1, 1, 1};
  h_in1 /= 3;
  double h_ans = (81.0 + 3.0 + 9.0) / 3.0;
  auto h_result = h_in0.dot(h_in1);
  CHECK(h_ans == h_result);
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 62") {
  using tybl::lynel::cvec2;
  using tybl::lynel::cvec3;
  using tybl::lynel::cvec4;
  using tybl::lynel::mat2;
  using tybl::lynel::mat3;
  using tybl::lynel::mat4;
  using tybl::lynel::rvec2;
  using tybl::lynel::rvec3;
  using tybl::lynel::rvec4;

  // A
  cvec2<int> a_in0 = {-1, 1};
  rvec2<int> a_in1 = {2, 3};
  mat2<int> a_ans = {{-2, 2}, {-3, 3}};
  auto a_result = a_in0 * a_in1;
  CHECK(a_ans == a_result);

  // B
  cvec2<int> b_in0 = {4, 6};
  rvec2<int> b_in1 = {2, 3};
  mat2<int> b_ans = {{8, 12}, {12, 18}};
  auto b_result = b_in0 * b_in1;
  CHECK(b_ans == b_result);

  // C
  cvec3<int> c_in0 = {-1, 0, 1};
  rvec3<int> c_in1 = {1, 2, 3};
  mat3<int> c_ans = {{-1, 0, 1}, {-2, 0, 2}, {-3, 0, 3}};
  auto c_result = c_in0 * c_in1;
  CHECK(c_ans == c_result);

  // D
  cvec4<int> d_in0 = {1, 3, 5, 7};
  rvec4<int> d_in1 = {0, 1, 1, 0};
  mat4<int> d_ans = {{0, 0, 0, 0}, {1, 3, 5, 7}, {1, 3, 5, 7}, {0, 0, 0, 0}};
  auto d_result = d_in0 * d_in1;
  CHECK(d_ans == d_result);
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 64") {
  // cvec3<int> a_in0 = { 1,3,2 };
  // cvec3<int> a_in1 = { -1,1,-2 };
  // cvec3<int> a_ans = { -1,3,-4 };
  // auto a_result = emul(a_in0,a_in1);
  // CHECK(a_ans == a_result);
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 65") {
  using tybl::lynel::cvec3;

  // A
  cvec3<int> a_in0 = {5, 3, 4};
  cvec3<int> a_in1 = {-2, 1, -1};
  cvec3<int> a_ans = {-7, -3, 11};
  auto a_result = a_in0.cross(a_in1);
  CHECK(a_ans == a_result);

  // B
  cvec3<int> b_in0 = {1, 1, 1};
  cvec3<int> b_in1 = {2, 2, 2};
  cvec3<int> b_ans = {0, 0, 0};
  auto b_result = b_in0.cross(b_in1);
  CHECK(b_ans == b_result);

  // C
  cvec3<int> c_in0 = {1, 0, 0};
  cvec3<int> c_in1 = {0, 1, 0};
  cvec3<int> c_ans = {0, 0, 1};
  auto c_result = c_in0.cross(c_in1);
  CHECK(c_ans == c_result);
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 67") {}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 78") {}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 86") {}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 90") {}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 97") {}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 112") {}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 126") {
  using tybl::lynel::mat2;
  using tybl::lynel::basic_matrix;

  // A
  mat2<int> a_in0 = {{1, 2}, {1, 3}};
  mat2<int> a_in1 = {{4, 2}, {3, 1}};
  mat2<int> a_ans = {{5, 4}, {4, 4}};
  auto a_result = a_in0 + a_in1;
  CHECK(a_ans == a_result);

  // B
  basic_matrix<int, 3, 2> b_in0 = {{0, -4, -3}, {5, 6, 0}};
  basic_matrix<int, 3, 2> b_in1 = {{0, 1, 1}, {1, 1, 0}};
  basic_matrix<int, 3, 2> b_ans = {{0, -3, -2}, {6, 7, 0}};
  auto b_result = b_in0 + b_in1;
  CHECK(b_ans == b_result);
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 128") {}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 130") {}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 142") {}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 147") {
  using tybl::lynel::basic_matrix;

  // A
  basic_matrix<double, 2, 3> a_in0 = {{3, 1}, {0, 1}, {3, 0}};
  basic_matrix<double, 3, 2> a_in1 = {{4, 0, 4}, {4, 1, 1}};
  basic_matrix<double, 2, 2> a_ans = {{24, 4}, {15, 5}};
  auto a_result = a_in0 * a_in1;
  CHECK(a_ans == a_result);

  // B (symbol algebra not implemented)
}

TEST_CASE("Linear Algebra: Theory, Intuition, Code - Practice Problems pg 148") {
  using tybl::lynel::basic_matrix;

  // A
  basic_matrix<double, 2, 3> a_in0 = {{3, 0}, {4, 4}, {0, 1}};
  basic_matrix<double, 3, 3> a_in1 = {{2, 4, 0}, {-1, 0, 1}, {2, 0, 1}};
  basic_matrix<double, 2, 3> a_ans = {{22, 16}, {-3, 1}, {6, 1}};
  auto a_result = a_in0 * a_in1;
  CHECK(a_result == a_ans);

  // B
  basic_matrix<double, 2, 2> b_in0 = {{1, 1}, {1, 2}};
  basic_matrix<double, 2, 2> b_in1 = {{3, 0}, {2, 1}};
  basic_matrix<double, 2, 2> b_ans = {{3, 3}, {3, 4}};
  auto b_result = b_in0 * b_in1;
  CHECK(b_result == b_ans);
}