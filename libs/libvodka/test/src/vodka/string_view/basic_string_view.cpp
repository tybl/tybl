// License: The Unlicense (https://unlicense.org)
#include "vodka/string_view/basic_string_view.hpp"

template struct tybl::vodka::basic_string_view<char>;

void create_string_view_object() {
  tybl::vodka::string_view sv("This");
  static_cast<void>(sv);
}
