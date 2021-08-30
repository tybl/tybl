// License: The Unlicense (https://unlicense.org)
#include "lynel/vector.hpp"

#include <algorithm>

namespace tybl::lynel {

template <typename T, size_t N>
constexpr void vector<T,N>::swap(vector<T,N>& a) noexcept(std::is_nothrow_swappable<value_type>::value) { std::swap_ranges(data(), data() + N, a.data()); }

} // namespace tybl::lynel
