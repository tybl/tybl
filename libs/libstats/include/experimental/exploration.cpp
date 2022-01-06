// License: The Unlicense (https://unlicense.org)
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <valarray>

#if 0
constexpr const size_t NUM_SAMPLES = 5;

class multivariate_distribution {
  std::size_t m_count { 0UL };
  std::valarray<double> m_means{};
  std::valarray<double> m_sum_sqrs {};
public:

  auto operator+=(std::valarray<double> const& x) -> multivariate_distribution& {
    m_count += 1;
    std::valarray<double> d = x - m_means;
    m_means += d / static_cast<double>(m_count);
    for (size_t i = 0; i < x.size(); ++i) {
      for (size_t j = 0; j < x.size(); ++j) {
        m_sums_of_squares.at(j).at(i) += d[i] * (x[j] - m_means[j]);
      }
    }
    std::cout << "Calculated means:\n";
    return *this;
  }
  [[nodiscard]] auto mean() const -> std::valarray<double> {
    return m_means;
  }
  [[nodiscard]] auto covariance() const -> std::array<std::array<double, N>, N> {
    std::array<std::array<double, N>, N> result {};
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        result.at(j).at(i) += m_sums_of_squares.at(j).at(i) / static_cast<double>(m_count - 1);
      }
    }
    return result;
  }
}; // class multivariate_distribution
#endif

auto main() -> int {
  #if 0
  const std::array<std::valarray<double>, NUM_SAMPLES> input = {
    {{ 4.0, 2.0, 0.60 },
    { 4.2, 2.1, 0.59 },
    { 3.9, 2.0, 0.58 },
    { 4.3, 2.1, 0.62 },
    { 4.1, 2.2, 0.63 }},
  };
  multivariate_distribution md;
  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t j = 0; j < input[i].size(); ++j) {
      std::cout << ' ' << input[i][j];
    }
    std::cout << std::endl;
    md += input[i];
  }
  std::cout << "Calculated means:\n";
  auto means = md.mean();
  for (auto const& m : means) {
    std::cout << m << std::endl;
  }
    std::cout << 'b' << std::endl;
  auto online_result = md.covariance();
  std::cout << "\nCalculated covariances:\n";
  for (auto const& r : online_result) {
    std::cout << "[";
    for (auto const cov : r) {
      std::cout << std::setw(8) << cov;
    }
    std::cout << " ]\n";
  }
  #endif
  for (int N = 1; N < 10; ++N) {
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j) 
        if (i <= j)
          std::cout << "N: " << N << ", i: " << i << ", j: " << j << ", i * N - i + j = " << i * (N - i) + j << std::endl;
    std::cout << std::endl;
  }
}

// License: The Unlicense (https://unlicense.org)
#include <array>
#include <cmath>
#include <iostream>
#include <limits>

constexpr const size_t NUM_VARS = 3;
constexpr const size_t NUM_SAMPLES = 5;

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
    return (1 < m_count) ? (m_sum_of_squares / static_cast<double>(m_count - 1))
                         : std::numeric_limits<double>::quiet_NaN();
  }

}; // class distribution

template <size_t N>
class multivariate_distribution {
  std::size_t m_count { 0UL };
  std::array<double, N> m_means {};
  std::array<std::array<double, N>, N> m_sums_of_squares {{}};
public:

  auto operator+=(std::array<double,N> const& x) -> multivariate_distribution& {
    m_count += 1;
    std::array<double, N> deltas {};
    for (size_t i = 0; i < N; ++i) {
      deltas.at(i) = x.at(i) - m_means.at(i);
      m_means.at(i) += deltas.at(i) / static_cast<double>(m_count);
    }
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j <= i; ++j) {
        m_sums_of_squares.at(j).at(i) += deltas.at(i) * (x.at(j) - m_means.at(j));
      }
    }
    return *this;
  }

  [[nodiscard]] auto mean() const -> std::array<double,N> {
    return m_means;
  }

  [[nodiscard]] auto covariance() const -> std::array<std::array<double,N>, N> {
    std::array<std::array<double,N>,N> result {};
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j <= i; ++j) {
        result.at(j).at(i) += m_sums_of_squares.at(j).at(i) / static_cast<double>(m_count - 1);
      }
    }
    return result;
  }

}; // class multivariate_distribution


auto main() -> int {
  const std::array<std::array<double, NUM_VARS>, NUM_SAMPLES> input = { {
    { 4.0, 2.0, 0.60 },
    { 4.2, 2.1, 0.59 },
    { 3.9, 2.0, 0.58 },
    { 4.3, 2.1, 0.62 },
    { 4.1, 2.2, 0.63 },
  } };
  std::array<distribution<double>, NUM_VARS> dists;
  for (auto const& r : input) {
    for (size_t i = 0; i < r.size(); ++i) {
      dists.at(i) += r.at(i);
    }
  }
  for (auto const& d : dists) {
    std::cout << "Mean: " << d.mean() << ", Variance: " << d.variance() << ", Max: " << d.maximum() << ", Min: " << d.minimum() << std::endl;
  }
  std::array<std::array<double, NUM_VARS>, NUM_VARS> cov_m{};
  for (size_t i = 0; i < NUM_VARS; ++i) {
    for (size_t j = 0; j < NUM_VARS; ++j) {
      double sum = 0.0;
      for (size_t k = 0; k < NUM_SAMPLES; ++k) {
        sum += (input.at(k).at(i) - dists.at(i).mean()) * (input.at(k).at(j) - dists.at(j).mean());
      }
      cov_m.at(i).at(j) = sum / (NUM_SAMPLES - 1);
      cov_m.at(j).at(i) = cov_m.at(i).at(j);
    }
  }
  std::cout << "Calculated covariances:\n";
  for (auto const& r : cov_m) {
    std::cout << "[";
    for (auto const cov : r) {
      std::cout << ' ' << cov;
    }
    std::cout << " ]\n";
  }
  multivariate_distribution<3> md;
  for (auto const& r : input) {
    md += r;
  }
  std::cout << "\n\nCalculated means:\n";
  auto means = md.mean();
  for (auto const& m : means) {
    std::cout << m << std::endl;
  }
  auto online_result = md.covariance();
  std::cout << "\n\nCalculated covariances:\n";
  for (auto const& r : online_result) {
    std::cout << "[";
    for (auto const cov : r) {
      std::cout << ' ' << cov;
    }
    std::cout << " ]\n";
  }
}
