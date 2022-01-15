// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_STACKSOLVER_INODE_HPP
#define TYBL_STACKSOLVER_INODE_HPP

#include "edge.hpp"

#include <vector>

struct i_node {
  virtual ~i_node() = default;
  virtual auto is_solved() const -> bool = 0;
  virtual std::vector<edge> generate_steps() const = 0;
  virtual i_node const* operator + (edge const& e) const = 0;
  virtual void print() const = 0;
  virtual void print_steps() const = 0;
  virtual size_t priority() const = 0;
  virtual size_t distance() const = 0;
  virtual size_t num_found() const = 0;
}; // struct i_node

#endif // TYBL_STACKSOLVER_INODE_HPP
