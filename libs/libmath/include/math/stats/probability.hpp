// License: The Unlicense (https://unlicense.org)
#pragma once

namespace vodka::math::stats {

class probability {
  double m_value;
public:

  explicit probability(double value)
    : m_value(value) { }

  explicit operator double() const {
    return m_value;
  }

  auto operator&&(probability const& o) const -> probability {
    return probability(mValue * o.mValue);
  }

  auto operator||(probability const& o) const -> probability {
    return probability(mValue + o.mValue - mValue * o.mValue);
  }

}; // class probability

} // namespace vodka::math::stats
