// License: The Unlicense (https://unlicense.org)
#include "executor.hpp"

#include "Board.hpp"

#include <cassert>
#include <iostream>

executor::executor(std::ifstream& p_file)
  : m_root(std::make_unique<const Board>(p_file))
{
  m_nodes.push_back(m_root.get());
}

auto executor::solve() -> i_node const* {
  while(!m_nodes.empty()) {
    auto const* node = m_nodes.back();
    m_nodes.pop_back();
    if (node->is_solved()) {
      return node;
    }
    auto edges = node->generate_steps();
    for (auto edge : edges) {
      auto const* n = *node + edge;
      if (nullptr != n) {
        m_nodes.push_back(n);
      }
    }
    std::make_heap(m_nodes.begin(), m_nodes.end(), node_weight());
    std::pop_heap(m_nodes.begin(), m_nodes.end(), node_weight());
  } // while (!empty)
  return nullptr;
}
