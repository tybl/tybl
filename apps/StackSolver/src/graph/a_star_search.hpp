// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_GRAPH_ASTARSEARCH_HPP
#define TYBL_GRAPH_ASTARSEARCH_HPP

#include <set>
#include <vector>

namespace tybl::graph {

template <typename Node>
struct a_star_search {
  using Iter = typename std::set<Node>::iterator;
  std::set<Node>    m_found;
  std::vector<Iter> m_work_queue;
public:

  struct node_weight {
    bool operator () (Iter const& lhs, Iter const& rhs) {
      auto lp = lhs->priority();
      auto rp = rhs->priority();
      return (lp < rp) || (lp == rp && lhs->distance() > rhs->distance());
    }
  }; // struct node_weight

  a_star_search(Node start) {
    auto res = m_found.insert(start);
    m_work_queue.push_back(res.first);
  }

  Iter search() {
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
      std::make_heap(m_work_queue.begin(), m_work_queue.end(), node_weight());
      std::pop_heap(m_work_queue.begin(), m_work_queue.end(), node_weight());
    }
    return m_found.end();
  }

  std::set<Node> const& get_found_nodes() const {
    return m_found;
  }

}; // struct a_star_search

} // namespace tybl::graph

#endif // TYBL_GRAPH_ASTARSEARCH_HPP
