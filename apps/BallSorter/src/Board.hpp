#ifndef BOARD_HPP
#define BOARD_HPP

#include "Edge.hpp"
#include "INode.hpp"

#include <memory>
#include <set>
#include <string>
#include <vector>

struct Board;

struct SharedStats {
  std::set<Board> m_boards;
  size_t m_max_stack_height;
}; // struct SharedStats

struct Board
  : public INode
{
  std::vector<std::string> m_contents;
  size_t m_priority;
  std::shared_ptr<SharedStats> m_stats;
  mutable Board const* m_parent;
  mutable size_t m_distance;
public:

  Board(std::istream& input);

  Board(Board const& o, Edge const& e);

  ~Board() override;

  bool is_solved() const override;

  std::vector<Edge> generate_steps() const override;

  INode const* operator + (Edge const& e) const override;

  void print() const override;

  void print_steps() const override;

  size_t priority() const override;

  size_t distance() const override;

  bool operator<(Board const& o) const;

private:

  void apply(Edge const& e);
  size_t count_suffix_matching(std::string const& s, char c) const;
  size_t calc_priority() const;
  bool is_full(std::string const& s) const;
  bool is_full_and_homogeneous(std::string const& s) const;
  bool is_homogeneous(std::string const& s) const;
  bool is_valid(Edge const& e) const;

};

#endif // BOARD_HPP
