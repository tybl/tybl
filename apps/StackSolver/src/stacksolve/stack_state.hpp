// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_STACKSOLVER_STACKSTATE_HPP
#define TYBL_STACKSOLVER_STACKSTATE_HPP

#include "vodka/dynarray_2d.hpp"

#include <vector>

namespace tybl::stacksolve {

class stack_state {
  vodka::dynarray_2d<char> m_contents;
  stack_state const* m_parent;
public:
  stack_state(vodka::dynarray_2d<char>&& p_contents)
    : m_contents(std::move(p_contents))
    , m_parent(nullptr)
  {
  }

  auto distance_from_start() const -> size_t {
    return (m_parent) ? (m_parent->distance_from_start() + 1) : 0;
  }

  auto priority() const -> size_t {
    return distance_from_start() + distance_to_goal();
  }

  auto operator<(stack_state const& p_o) const -> bool {
    return m_contents < p_o.m_contents;
  }

  auto distance_to_goal() const -> size_t {
    size_t result = 0;
    for (size_t i = 0UL; i < m_contents.rows(); ++i) {
      result += num_to_move(m_contents.row(i));
    }
    return result;
  }

  auto is_goal() const -> bool {
    for (size_t i = 0UL; i < m_contents.rows(); ++i) {
      if (!(is_empty(i) || is_full_and_homogeneous(m_contents.row(i)))) {
        return false;
      }
    }
    return true;
  }

  auto get_adjacent() const -> std::vector<stack_state> {
    // TODO
    return std::vector<stack_state>();
  }

  bool is_empty(size_t p_row) const {
    return '0' == m_contents(p_row,0);
  }

  bool is_full_and_homogeneous(std::span<const char> p_row) const {
    for (auto const c : p_row) {
      if (p_row.front() != c) { return false; }
    }
    return true;
  }

  size_t num_to_move(std::span<const char> p_row) const {
    size_t result = 0;
    for (auto c : p_row) {
      result += static_cast<size_t>(p_row.front() != c);
    }
    return result;
  }

}; // class stack_state

} // namespace tybl::stacksolve

#endif // TYBL_STACKSOLVER_STACKSTATE_HPP
