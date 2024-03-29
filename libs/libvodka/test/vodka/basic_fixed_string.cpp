// License: The Unlicense (https://unlicense.org)
#include <vodka/basic_fixed_string.hpp>

#include <doctest/doctest.h>

#include <cstring>

template <tybl::vodka::basic_fixed_string Name>
auto get_name() -> const char* {
  return static_cast<const char*>(Name);
}

TEST_CASE("tybl::vodka::basic_fixed_string") {
  constexpr tybl::vodka::basic_fixed_string fs1{"Hello"};
  tybl::vodka::basic_fixed_string fs2{"World"};
  CHECK(fs1.size() == 5);
  CHECK(0 == std::strncmp(fs1.m_buffer.data(),"Hello", fs1.size()));
  CHECK(fs1.size() == fs2.size());
  CHECK(0 != std::strncmp(fs1.m_buffer.data(), static_cast<const char*>(fs2), fs1.size()));
  CHECK(0 == std::strncmp(get_name<fs1>(), static_cast<const char*>(fs1), fs1.size()));
}
