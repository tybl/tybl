#include "Executor.hpp"

#include "Board.hpp"

#include <cassert>
#include <iostream>

Executor::Executor(std::ifstream& file)
  : m_nodes()
  , m_root(std::make_unique<const Board>(file))
{
  m_nodes.push_back(m_root.get());
}

INode const* Executor::solve() {
  while(!m_nodes.empty()) {
    auto node = m_nodes.back();
    m_nodes.pop_back();
    if (node->is_solved()) {
      return node;
    }
    auto edges = node->generate_steps();
    for (auto edge : edges) {
      auto* n = *node + edge;
      if (n) {
        m_nodes.push_back(n);
      }
    }
    std::make_heap(m_nodes.begin(), m_nodes.end(), NodeWeight());
    std::pop_heap(m_nodes.begin(), m_nodes.end(), NodeWeight());
  } // while (!empty)
  return nullptr;
}
