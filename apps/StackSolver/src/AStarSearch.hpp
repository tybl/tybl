// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_GRAPH_ASTARSEARCH_HPP
#define TYBL_GRAPH_ASTARSEARCH_HPP

#include <cassert>
#include <fstream>
#include <set>
#include <vector>

struct StacksState {
  std::vector<std::string> m_contents;
  StacksState const* m_parent;
public:
  StacksState(std::istream& input)
    : m_parent(nullptr)
  {
    std::string line;
    std::getline(input, line);
    m_contents.resize(line.size());
    while (input.good()) {
      assert(line.size() == m_contents.size());
      for (size_t i = 0; i < line.size(); ++i) {
        // TODO
      }
      std::getline(input, line);
    }
  }
  auto is_goal() const -> bool {
  }
  auto get_adjacent() const -> std::vector<StacksState> {
  }
  auto distance() const -> size_t {
    return (m_parent) ? (m_parent->distance() + 1) : 0;
  }
  auto priority() const -> size_t {
  }
  auto operator<(StacksState const& o) const -> bool {
    return m_contents < o.m_contents;
  }
}; // struct StacksState

namespace tybl::graph {

template <typename Node>
struct AStarSearch {
  using Iter = std::set<Node>::iterator;
  std::set<Node>    m_found;
  std::vector<Iter> m_work_queue;
public:

  struct BoardWeight {
    bool operator () (Iter lhs, Iter rhs) {
      auto lp = lhs->priority();
      auto rp = rhs->priority();
      return (lp < rp) || (lp == rp && lhs->distance() > rhs->distance());
    }
  }; // struct BoardWeight

  AStarSearch(Node start) {
    auto res = m_found.insert(start);
    m_work_queue.push_back(res.first);
  }

  Iter Search() {
    while (!m_work_queue.empty()) {
      auto curr = m_work_queue.back();
      m_work_queue.pop_back();
      if (curr->is_goal()) {
        return curr;
      }
      auto nodes = curr->get_adjacent();
      for (auto n : nodes) {
        auto res = m_found.insert(n);
        if (res.second) {
          m_work_queue.push_back(res.first);
        }
      }
      std::make_heap(m_work_queue.begin(), m_work_queue.end(), BoardWeight());
      std::pop_heap(m_work_queue.begin(), m_work_queue.end(), BoardWeight());
    }
    return m_found.end();
  }

  std::set<Node> const& get_found_nodes() const {
    return m_found;
  }

}; // struct AStarSearch

} // namespace tybl::graph

#endif // TYBL_GRAPH_ASTARSEARCH_HPP
