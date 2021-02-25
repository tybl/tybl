#include "vodka/type_traits/integral_constant.hpp"
#include "vodka/type_traits/is_same.hpp"

int main() {
  using two_t  = tybl::vodka::integral_constant<int, 2>;
  using four_t = tybl::vodka::integral_constant<int, 4>;

  static_assert(!tybl::vodka::is_same<two_t, four_t>::value, "two_t and four_t are not equal!"); 

  static_assert(two_t::value * 2 == four_t::value, "2*2 != 4");

  enum class my_enum { e1, e2 };
  using my_enum_e1 = tybl::vodka::integral_constant<my_enum, my_enum::e1>;
  using my_enum_e2 = tybl::vodka::integral_constant<my_enum, my_enum::e2>;

  static_assert(my_enum_e1::value != my_enum::e2, "my_enum_e1::value != my_enum::e2");

  static_assert(tybl::vodka::is_same<my_enum_e2, my_enum_e2>::value, "my_enum_e2 != my_enum_e2");
}
