// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_STACKSOLVER_INODE_HPP
#define TYBL_STACKSOLVER_INODE_HPP

#include "edge.hpp"

#include <cstddef>
#include <vector>

struct i_node {
  virtual ~i_node() = 0;
  [[nodiscard]] virtual auto is_solved() const -> bool = 0;
  [[nodiscard]] virtual auto generate_steps() const -> std::vector<edge> = 0;
  virtual auto operator+(edge const& p_e) const -> i_node const* = 0;
  virtual void print() const = 0;
  virtual void print_steps() const = 0;
  [[nodiscard]] virtual auto priority() const -> size_t = 0;
  [[nodiscard]] virtual auto distance() const -> size_t = 0;
  [[nodiscard]] virtual auto num_found() const -> size_t = 0;
}; // struct i_node

#endif // TYBL_STACKSOLVER_INODE_HPP
