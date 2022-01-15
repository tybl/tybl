// License: The Unlicense (https://unlicense.org)
#ifndef BOARD_HPP
#define BOARD_HPP

#include "edge.hpp"
#include "i_node.hpp"

#include <memory>
#include <set>
#include <string>
#include <vector>

struct Board;

struct shared_stats {
  std::set<Board> m_boards;
  size_t m_max_stack_height;
}; // struct shared_stats

struct Board
  : public i_node {
  std::vector<std::string> m_contents;
  size_t m_priority;
  std::shared_ptr<shared_stats> m_stats;
  size_t m_id;
  mutable Board const* m_parent;
  mutable size_t m_distance;
public:

  Board(std::istream& input);

  Board(Board const& o, edge const& e);

  ~Board() override;

  auto is_solved() const -> bool override;

  auto generate_steps() const -> std::vector<edge> override;

  auto operator + (edge const& e) const -> i_node const* override;

  void print() const override;

  void print_steps() const override;

  auto priority() const -> size_t override;

  auto distance() const -> size_t override;

  auto operator<(Board const& o) const -> bool;

  auto num_found() const -> size_t override;

public:

  void apply(edge const& e);
  static auto count_suffix_matching(std::string const& s, char c) -> size_t;
  size_t calc_priority() const;
  bool is_full(std::string const& s) const;
  bool is_full_and_homogeneous(std::string const& s) const;
  static auto is_homogeneous(std::string const& s) -> bool;
  bool is_valid(edge const& e) const;

};

#endif // BOARD_HPP
