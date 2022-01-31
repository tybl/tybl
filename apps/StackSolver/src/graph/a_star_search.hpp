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
  std::set<Node> m_found;
  std::vector<Iter> m_work_queue;

  struct node_weight {
    auto operator()(Iter const& p_lhs, Iter const& p_rhs) const -> bool {
      auto lp = p_lhs->priority();
      auto rp = p_rhs->priority();
      return (lp < rp) || (lp == rp && p_lhs->distance() > p_rhs->distance());
    }
  }; // struct node_weight

  explicit a_star_search(Node p_start) {
    auto res = m_found.insert(p_start);
    m_work_queue.push_back(res.first);
  }

  auto search() -> Iter {
    while (!m_work_queue.empty()) {
      auto curr = m_work_queue.back();
      m_work_queue.pop_back();
      if (curr->is_goal()) {
        return curr;
      }
      for (auto nodes = curr->get_adjacent(); auto n : nodes) {
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

  [[nodiscard]] auto get_found_nodes() const -> std::set<Node> const& { return m_found; }

}; // struct a_star_search

} // namespace tybl::graph

#endif // TYBL_GRAPH_ASTARSEARCH_HPP
