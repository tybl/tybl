// License: The Unlicense (https://unlicense.org)
#include "lynel/matrix.hpp"

#include <doctest/doctest.h>

using namespace tybl::lynel;

TEST_CASE("tybl::lynel::matrix") {
  matrix<double,3,3> m;
  m(1,1) = 5.5;
  CHECK(m(1,1) == 5.5);
}

TEST_CASE("matrix::operator==()") {
  matrix<double,3,3> a = { 0,1,2,3,4,5,6,7,8 };
  matrix<double,3,3> b = { 0,1,2,3,4,5,6,7,8 };
  matrix<double,3,3> c = { 1,1,2,3,4,5,6,7,8 };
  matrix<double,3,3> d = { 0,1,2,3,4,5,6,7,9 };
  CHECK(a == a);
  CHECK(a == b);
  CHECK(!(a == c));
  CHECK(!(b == d));
}

TEST_CASE("aggregate initialization and correct positional assignment of values") {
  matrix<double,3,3> m = {
    0,1,2,
    3,4,5,
    6,7,8
  };
  CHECK(m(0,0) == 0.0);
  CHECK(m(0,1) == 1.0);
  CHECK(m(0,2) == 2.0);
  CHECK(m(1,0) == 3.0);
  CHECK(m(1,1) == 4.0);
  CHECK(m(1,2) == 5.0);
  CHECK(m(2,0) == 6.0);
  CHECK(m(2,1) == 7.0);
  CHECK(m(2,2) == 8.0);
}

TEST_CASE("scalar multiplication") {
  matrix<double,3,3> m = { 0,1,2, 3,4,5, 6,7,8 };
  matrix<double,3,3> a = { 0,2,4,6,8,10,12,14,16 };
  m *= 2.0;
  CHECK(a == m);
}

TEST_CASE("transpose 3x3") {
  matrix<double,3,3> m = { 0,1,2,3,4,5,6,7,8 };
  matrix<double,3,3> mt = { 0,3,6,1,4,7,2,5,8 };
  auto n = transpose(m);
  CHECK(n == mt);
}

TEST_CASE("Linear Algebra:Theory, Intuition, Code - Practice Problems pg 33") {
  // A
  matrix<double,1,4> a0 = { 4,5,1,0 };
  matrix<double,1,4> a1 = { -4,-3,3,10 };
  matrix<double,1,4> aa = { 0,2,4,10 };
  auto ar = add(a0,a1);
  CHECK(aa == ar);

  // B
  matrix<double,3,1> b0 = { 4,2,0 };
  matrix<double,3,1> b1 = { 6,-4,60 };
  matrix<double,3,1> b2 = { 2,-5,40 };
  matrix<double,3,1> ba = { 0,1,-20 };
  auto br = add(subtract(b0,b1),b2);
  CHECK(ba == br);

  // C
  matrix<double,2,1> c0 = { 1,0 };
  matrix<double,2,1> c1 = { 1,2 };
  matrix<double,2,1> ca = { 2,2 };
  auto cr = add(c0,c1);
  CHECK(ca == cr);

  // D
  matrix<double,2,1> d0 = { 2,2 };
  matrix<double,2,1> d1 = { 3,4 };
  matrix<double,2,1> da = { -1,-2 };
  auto dr = subtract(d0,d1);
  CHECK(da == dr);

  // E
  matrix<double,2,1> e0 = { -3,1 };
  matrix<double,2,1> e1 = { 3,-1 };
  matrix<double,2,1> ea = { 0,0 };
  auto er = add(e0,e1);
  CHECK(ea == er);

  // F
  matrix<double,2,1> f0 = { 1,4 };
  matrix<double,2,1> f1 = { 2,8 };
  matrix<double,2,1> fa = { 3,12 };
  auto fr = add(f0,f1);
  CHECK(fa == fr);

}

TEST_CASE("Linear Algebra:Theory, Intuition, Code - Practice Problems pg 147") {
  // A
  matrix<double,2,3> a0 = { 3,0,3,1,1,0 };
  matrix<double,3,2> a1 = { 4,4,0,1,4,1 };
  matrix<double,2,2> aa = { 24,15,4,5};
  auto ar = multiply(a0,a1);
  CHECK(aa == ar);

  // B (symbol algebra not implemented)
}

TEST_CASE("Linear Algebra:Theory, Intuition, Code - Practice Problems pg 148") {
  // A
  matrix<double,2,3> a0 = { 3,4,0,0,4,1 };
  matrix<double,3,3> a1 = { 2,-1,2,4,0,0,0,1,1 };
  matrix<double,2,3> aa = { 22,-3,6,16,1,1 };
  auto ar = multiply(a0,a1);
  CHECK(ar == aa);

  // B
  matrix<double,2,2> b0 = { 1,1,1,2 };
  matrix<double,2,2> b1 = { 3,2,0,1 };
  matrix<double,2,2> ba = { 3,3,3,4 };
  auto br = multiply(b0,b1);
  CHECK(br == ba);
}
