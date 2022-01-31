// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_STACKSOLVER_EXECUTOR_HPP
#define TYBL_STACKSOLVER_EXECUTOR_HPP

#include "i_node.hpp"
#include "node_weight.hpp"

#include <fstream>
#include <memory>
#include <queue>
#include <vector>

struct executor {
  std::vector<i_node const*> m_nodes;
  std::unique_ptr<const i_node> m_root;

  explicit executor(std::ifstream& p_file);

  auto solve() -> i_node const*;

}; // struct executor

#endif // TYBL_STACKSOLVER_EXECUTOR_HPP
