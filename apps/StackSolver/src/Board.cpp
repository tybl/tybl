// License: The Unlicense (https://unlicense.org)
#include "Board.hpp"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <map>

#include <iostream>

Board::Board(std::istream& input)
  : m_priority(0)
  , m_stats(std::make_shared<SharedStats>())
  , m_id(0)
  , m_parent(nullptr)
  , m_distance(0)
{
  std::string line;
  std::getline(input, line);
  m_contents.resize(line.size());
  while (input.good()) {
    assert(line.size() == m_contents.size());
    m_stats->m_max_stack_height += 1;
    for (size_t i = 0; i < line.size(); ++i) {
      if (line[i] != '0') {
        m_contents[i].insert(m_contents[i].begin(), line[i]);
      }
    }
    std::getline(input, line);
  }
  m_priority = calc_priority();
  m_stats->m_boards.insert(*this);
}

Board::Board(Board const& o, Edge const& e)
  : m_contents(o.m_contents)
  , m_priority(0)
  , m_stats(o.m_stats)
  , m_id(m_stats->m_boards.size())
  , m_parent(&o)
  , m_distance(o.m_distance + 1)
{
  apply(e);
}


Board::~Board() = default;

auto Board::is_solved() const -> bool {
  return std::ranges::all_of(m_contents, [this](std::string const& s) {
    return s.empty() || is_full_and_homogeneous(s);
  });
}

auto Board::generate_steps() const -> std::vector<Edge> {
  std::vector<Edge> result;
  for (uint8_t i = 0; i < static_cast<uint8_t>(m_contents.size()); ++i) {
    for (uint8_t j = 0; j < static_cast<uint8_t>(m_contents.size()); ++j) {
      Edge e{i,j};
      if (is_valid(e)) {
        result.push_back(e);
      }
    }
  }
  //std::cout << m_id << "\t: " << m_stats->m_boards.size() << "\t: " << result.size() << "\t: " << distance() << "\n";
  return result;
}

auto Board::operator+(Edge const& e) const -> INode const* {
  auto result = m_stats->m_boards.emplace(*this, e);
  Board const& b = *result.first;
  if (result.second) {
    return &b;
  }
  if (distance() + 1 < b.distance()) {
    b.m_parent = this;
    b.m_distance = m_distance + 1;
  }
  return nullptr;
}

void Board::print() const {
  std::cout << "\nd: " << distance() << ", p(): " << priority();
  const size_t height = m_stats->m_max_stack_height;
  for (size_t i = 0; i < height; ++i) {
    std::cout << '\n';
    size_t r = (height - 1) - i;
    for (auto const& c : m_contents) {
      if (r < c.size()) {
        std::cout << c.at(r);
      } else {
        std::cout << ' ';
      }
    }
  }
}

size_t Board::num_found() const {
  return m_stats->m_boards.size();
}

void Board::print_steps() const {
  if (nullptr != m_parent) {
    m_parent->print_steps();
  }
  print();

  std::string ignore;
  std::getline(std::cin, ignore);
}

auto Board::priority() const -> size_t {
  return m_priority;
}

auto Board::distance() const -> size_t {
  return m_distance;
}

auto Board::operator<(Board const& o) const -> bool {
  return m_contents < o.m_contents;
}

void Board::apply(Edge const& e) {
  m_contents.at(e.StackTo).push_back(m_contents.at(e.StackFrom).back());
  m_contents.at(e.StackFrom).pop_back();
  m_priority = calc_priority();
}

auto Board::calc_priority() const -> size_t {
  size_t result = 0;
  for (auto const& s : m_contents) {
    if (!s.empty()) {
      result += (s.size() - s.find_last_not_of(s.back()) - 1);
    }
  }
  return result;
}

auto Board::count_suffix_matching(std::string const& s, char c) -> size_t {
  auto i = s.rbegin();
  while (i != s.rend() && *i == c) { ++i; }
  return std::distance(s.rbegin(), i);
}

auto Board::is_valid(Edge const& e) const -> bool {
  if (e.StackFrom == e.StackTo) { return false; }
  if (m_contents.at(e.StackFrom).empty()) { return false; }
  if (is_full(m_contents.at(e.StackTo))) { return false; }
  if (is_full_and_homogeneous(m_contents[e.StackFrom])) { return false; }
  if (m_contents.at(e.StackTo).empty()) { return true; }
  return m_contents[e.StackTo].back() == m_contents[e.StackFrom].back();
}

auto Board::is_homogeneous(std::string const& s) -> bool {
  return std::all_of(s.begin(), s.end(), [&](char c){ return s.front() == c; });
}

auto Board::is_full(std::string const& s) const -> bool {
  return s.size() == m_stats->m_max_stack_height;
}

auto Board::is_full_and_homogeneous(std::string const& s) const -> bool {
  return is_full(s) && is_homogeneous(s);
}
