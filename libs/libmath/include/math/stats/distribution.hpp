// License: The Unlicense (https://unlicense.org)
#pragma once

#include <cmath>
#include <limits>

namespace tybl::math::stats {

template <typename Type>
class distribution {
  std::size_t m_count     { 0UL };
  double m_mean           { 0.0 };
  double m_sum_of_squares { 0.0 };
  Type m_maximum          { std::numeric_limits<Type>::lowest() };
  Type m_minimum          { std::numeric_limits<Type>::max() };
public:

  constexpr auto operator+=(Type x) -> distribution& {
    m_count += 1;
    double delta = static_cast<double>(x) - m_mean;
    m_mean += delta / static_cast<double>(m_count);
    m_sum_of_squares += delta * (static_cast<double>(x) - m_mean);
    m_maximum = std::max(x, m_maximum);
    m_minimum = std::min(x, m_minimum);
    return *this;
  }

  [[nodiscard]] constexpr auto count() const -> std::size_t {
    return m_count;
  }

  [[nodiscard]] constexpr auto maximum() const -> Type {
    return m_maximum;
  }

  [[nodiscard]] constexpr auto minimum() const -> Type {
    return m_minimum;
  }

  [[nodiscard]] constexpr auto mean() const -> double {
    return m_mean;
  }

  [[nodiscard]] auto std_dev() const -> double {
    return std::sqrt(variance());
  }

  [[nodiscard]] auto variance() const -> double {
    return (1 < m_count) ? (m_sum_of_squares / (m_count - 1))
                         : std::numeric_limits<double>::quiet_NaN();
  }

}; // class distribution

} // namespace tybl::math::stats
