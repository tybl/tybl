// License: The Unlicense (https://unlicense.org)
#include "executor.hpp"

#include "Board.hpp"

#include <cassert>
#include <iostream>

executor::executor(std::ifstream& p_file)
  : m_root(std::make_unique<const Board>(p_file)) {
  m_nodes.push_back(m_root.get());
}

auto executor::solve() -> i_node const* {
  while (!m_nodes.empty()) {
    auto const* node_p = m_nodes.back();
    m_nodes.pop_back();
    if (node_p->is_solved()) {
      return node_p;
    }
    auto edges = node_p->generate_steps();
    for (auto edge : edges) {
      auto const* next_p = *node_p + edge;
      if (nullptr != next_p) {
        m_nodes.push_back(next_p);
      }
    }
    std::make_heap(m_nodes.begin(), m_nodes.end(), node_weight());
    std::pop_heap(m_nodes.begin(), m_nodes.end(), node_weight());
  } // while (!empty)
  return nullptr;
}
