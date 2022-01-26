// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_MATH_STATS_PROBABILITY_HPP
#define TYBL_MATH_STATS_PROBABILITY_HPP

namespace vodka::math::stats {

class probability {
  double m_value;

public:
  explicit probability(double value)
    : m_value(value) {}

  explicit operator double() const { return m_value; }

  auto operator&&(probability const& o) const -> probability { return probability(m_value * o.m_value); }

  auto operator||(probability const& o) const -> probability {
    return probability(m_value + o.m_value - m_value * o.m_value);
  }

}; // class probability

} // namespace vodka::math::stats

#endif TYBL_MATH_STATS_PROBABILITY_HPP