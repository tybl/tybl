// License: The Unlicense (https://unlicense.org)
#ifndef INODE_HPP
#define INODE_HPP

#include "Edge.hpp"

#include <vector>

struct INode {
  virtual ~INode() = default;
  virtual auto is_solved() const -> bool = 0;
  virtual std::vector<Edge> generate_steps() const = 0;
  virtual INode const* operator + (Edge const& e) const = 0;
  virtual void print() const = 0;
  virtual void print_steps() const = 0;
  virtual size_t priority() const = 0;
  virtual size_t distance() const = 0;
  virtual size_t num_found() const = 0;
}; // struct INode

#endif // INODE_HPP
