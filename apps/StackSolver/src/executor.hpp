// License: The Unlicense (https://unlicense.org)
#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include "i_node.hpp"
#include "node_weight.hpp"

#include <fstream>
#include <memory>
#include <queue>
#include <vector>

struct executor {
  std::vector<i_node const*> m_nodes;
  std::unique_ptr<const i_node> m_root;
public:
  executor(std::ifstream& file);

  i_node const* solve();

}; // struct executor

#endif // EXECUTOR_HPP
