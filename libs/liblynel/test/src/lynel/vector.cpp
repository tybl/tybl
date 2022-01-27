// License: The Unlicense (https://unlicense.org)

#include "lynel/vector.hpp"
#include "lynel/vector_ops.hpp"

#include <doctest/doctest.h>

TEST_CASE("tybl::lynel::vector") {
  tybl::lynel::vector<double, 3> v;
  v(1) = 5.5;
  CHECK(v(1) == 5.5);
}

TEST_CASE("Associative law for vector addition") {
  tybl::lynel::vector<double, 3> a{1, 2, 3};
  tybl::lynel::vector<double, 3> b{4, 5, 6};
  tybl::lynel::vector<double, 3> c{7, 8, 9};

  auto l = (a + b) + c;
  auto r = a + (b + c);

  CHECK(l == r);
}

TEST_CASE("Commutative law for vector addition") {
  tybl::lynel::vector<double, 3> a{1, 2, 3};
  tybl::lynel::vector<double, 3> b{4, 5, 6};

  auto l = a + b;
  auto r = b + a;

  CHECK(l == r);
}

TEST_CASE("Associate law for scalar-vector multiplication") {
  tybl::lynel::vector<double, 3> a{1, 2, 3};
  double s = 5.0;
  double t = 3.0;

  auto l = (s * t) * a;
  auto r = s * (t * a);

  CHECK(l == r);
}

TEST_CASE("Commutative law for scalar-vector multiplication") {
  tybl::lynel::vector<double, 3> a{1, 2, 3};
  tybl::lynel::vector<double, 3> b{4, 5, 6};
  double t = 9.0;

  auto l = t * (a + b);
  auto r = (t * a) + (t * b);

  CHECK(l == r);
}

TEST_CASE("dot product") {
  tybl::lynel::vector<double, 3> a{1, 0, 0};
  tybl::lynel::vector<double, 3> b{0, 2, 0};
  tybl::lynel::vector<double, 3> c{2, 2, 2};

  CHECK(1.0 == dot_product(a, a));
  CHECK(0.0 == dot_product(a, b));
  CHECK(4.0 == dot_product(b, b));
  CHECK(12.0 == dot_product(c, c));
}

TEST_CASE("Commutative law for the dot product") {
  tybl::lynel::vector<double, 3> a{1, 2, 3};
  tybl::lynel::vector<double, 3> b{4, 5, 6};

  auto l = dot_product(a, b);
  auto r = dot_product(b, a);

  CHECK(l == r);
}

TEST_CASE("Distributive law for the dot product") {
  tybl::lynel::vector<double, 3> a{1, 2, 3};
  tybl::lynel::vector<double, 3> b{4, 5, 6};
  tybl::lynel::vector<double, 3> c{7, 8, 9};

  auto l = dot_product(a, (b + c));
  auto r = dot_product(a, b) + dot_product(a, c);

  CHECK(l == r);
}

TEST_CASE("Scalar factorization for the dot product") {
  tybl::lynel::vector<double, 3> a{1, 2, 3};
  tybl::lynel::vector<double, 3> b{4, 5, 6};
  double t = 9.0;

  auto l = dot_product(t * a, b);
  auto c = dot_product(a, t * b);
  auto r = t * dot_product(a, b);

  CHECK(l == c);
  CHECK(c == r);
}
