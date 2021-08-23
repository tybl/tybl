// License: The Unlicense (https://unlicense.org)
#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include "INode.hpp"
#include "NodeWeight.hpp"

#include <fstream>
#include <memory>
#include <queue>
#include <vector>

struct Executor {
  std::vector<INode const*> m_nodes;
  std::unique_ptr<const INode> m_root;
public:

  Executor(std::ifstream& file);

  INode const* solve();

}; // struct Executor

#endif // EXECUTOR_HPP
