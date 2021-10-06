// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_GRAPH_ASTARSEARCH_HPP
#define TYBL_GRAPH_ASTARSEARCH_HPP

#include <cassert>
#include <fstream>
#include <memory>
#include <set>
#include <span>
#include <vector>

template <typename T>
struct dynarray2D {

  // types:
  using value_type = T;
  using reference = value_type&;
  using const_reference = value_type const&;
  using size_type = size_t;

private:
  std::unique_ptr<value_type[]> m_data;
  size_type m_rows;
  size_type m_cols;
public:

  dynarray2D(size_t r, size_t c)
    : m_data((0 < c && 0 < r) ? (std::make_unique<char[]>(c*r)) : nullptr)
    , m_rows(r)
    , m_cols(c)
  {
  }

  dynarray2D(dynarray2D<char>&& o)
    : m_data(std::move(o.m_data))
    , m_rows(o.m_rows)
    , m_cols(o.m_cols)
  {
  }

  dynarray2D(dynarray2D<char> const& o)
    : m_data(o.m_data ? std::make_unique<char[]>(o.m_cols*o.m_rows) : nullptr)
    , m_rows(o.m_rows)
    , m_cols(o.m_cols)
  {
    memcpy(m_data.get(), o.m_data.get(), m_cols*m_rows);
  }

  ~dynarray2D() = default;

  const_reference operator()(size_t r, size_t c) const {
    return m_data[m_cols*r + c];
  }

  reference operator()(size_t r, size_t c) {
    return m_data[m_cols*r + c];
  }

  bool operator<(dynarray2D const& o) const {
    char* first1 = m_data.get();
    char* first2 = o.m_data.get();
    char* last1 = first1 + m_cols * m_rows;
    char* last2 = first2 + o.m_cols * o.m_rows;
    for (;(first1 != last1) && (first2 != last2); ++first1, ++first2) {
      if (*first1 < *first2) return true;
      if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
  }

  size_type cols() const { return m_cols; }

  size_type rows() const { return m_rows; }

  std::span<const value_type> row(size_t r) const {
    return std::span<const value_type>(m_data.get() + m_cols*r, m_cols);
  }

}; // struct dynarray2D

struct StacksState {
  dynarray2D<char> m_contents;
  StacksState const* m_parent;
public:
  StacksState(dynarray2D<char>&& contents)
    : m_contents(std::move(contents))
    , m_parent(nullptr)
  {
  }

  auto distance_from_start() const -> size_t {
    return (m_parent) ? (m_parent->distance_from_start() + 1) : 0;
  }

  auto priority() const -> size_t {
    return distance_from_start() + distance_to_goal();
  }

  auto operator<(StacksState const& o) const -> bool {
    return m_contents < o.m_contents;
  }

  auto distance_to_goal() const -> size_t {
    size_t result = 0;
    for (size_t i = 0UL; i < m_contents.rows(); ++i) {
      result += num_to_move(m_contents.row(i));
    }
    return result;
  }

  auto is_goal() const -> bool {
    for (size_t i = 0UL; i < m_contents.rows(); ++i) {
      if (!(is_empty(i) || is_full_and_homogeneous(m_contents.row(i)))) {
        return false;
      }
    }
    return true;
  }

  auto get_adjacent() const -> std::vector<StacksState> {
    return std::vector<StacksState>();
  }

  bool is_empty(size_t row) const {
    return '0' == m_contents(row,0);
  }

  bool is_full_and_homogeneous(std::span<const char> row) const {
    for (auto const c : row) {
      if (row.front() != c) { return false; }
    }
    return true;
  }

  size_t num_to_move(std::span<const char> row) const {
    size_t result = 0;
    for (auto c : row) {
      result += static_cast<size_t>(row.front() != c);
    }
    return result;
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
