// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_STATS_DISTRIBUTION_HPP
#define TYBL_STATS_DISTRIBUTION_HPP

// TODO(tybl): Replace Eigen with liblynel
#include <Eigen/Dense>

#include <cmath>
#include <limits>

namespace tybl::stats {

template <typename Type>
class distribution {
  std::size_t m_count{0UL};
  double m_mean{0.0};
  double m_sum_of_squares{0.0};
  Type m_maximum{std::numeric_limits<Type>::lowest()};
  Type m_minimum{std::numeric_limits<Type>::max()};

public:
  // TODO(tybl): Unintuitive use of operator+=, replace with regular function
  constexpr auto operator+=(Type p_x) -> distribution& {
    m_count += 1;
    double delta = static_cast<double>(p_x) - m_mean;
    m_mean += delta / static_cast<double>(m_count);
    m_sum_of_squares += delta * (static_cast<double>(p_x) - m_mean);
    m_maximum = std::max(p_x, m_maximum);
    m_minimum = std::min(p_x, m_minimum);
    return *this;
  }

  [[nodiscard]] constexpr auto count() const -> std::size_t { return m_count; }

  [[nodiscard]] constexpr auto maximum() const -> Type { return m_maximum; }

  [[nodiscard]] constexpr auto minimum() const -> Type { return m_minimum; }

  [[nodiscard]] constexpr auto mean() const -> double { return m_mean; }

  [[nodiscard]] auto pop_stddev() const -> double { return std::sqrt(pop_var()); }

  [[nodiscard]] auto samp_stddev() const -> double { return std::sqrt(samp_var()); }

  [[nodiscard]] auto pop_var() const -> double {
    return (0 < m_count) ? (m_sum_of_squares / static_cast<double>(m_count)) : std::numeric_limits<double>::quiet_NaN();
  }

  [[nodiscard]] auto samp_var() const -> double {
    return (1 < m_count) ? (m_sum_of_squares / static_cast<double>(m_count - 1))
                         : std::numeric_limits<double>::quiet_NaN();
  }

}; // class distribution

// TODO(tybl): Class name is not descriptive
template <size_t N>
class dist {
  static_assert(0 < N, "");

  // types:
  using value_type = double;
  using vector_type = Eigen::Matrix<value_type, N, 1>;
  using matrix_type = Eigen::Matrix<value_type, N, N>;
  using size_type = std::size_t;

  // member variables:
  size_type m_count{0UL};
  vector_type m_means{vector_type::Zero()};
  matrix_type m_covars{matrix_type::Zero()};

public:
  constexpr auto insert(Eigen::Matrix<double, N, 1> const& p_xs) -> void {
    m_count += 1;
    vector_type deltas = p_xs - m_means;
    m_means += deltas / m_count;
    matrix_type covar_deltas = (p_xs - m_means) * deltas.transpose() - m_covars;
    m_covars += covar_deltas / m_count;
  }

  constexpr auto means() const -> vector_type const& { return m_means; }

  constexpr auto covariance() const -> matrix_type const& { return m_covars; }

}; // class dist

} // namespace tybl::stats

#endif // TYBL_STATS_DISTRIBUTION_HPP
