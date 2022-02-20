// License: The Unlicense (https://unlicense.org)
#include "Board.hpp"

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <map>

#include <iostream>

Board::Board(std::istream& p_input)
  : m_stats(std::make_shared<shared_stats>())
  , m_id(0)
  , m_parent(nullptr)
  , m_distance(0) {
  std::string line;
  std::getline(p_input, line);
  m_contents.resize(line.size());
  while (p_input.good()) {
    assert(line.size() == m_contents.size());
    m_stats->m_max_stack_height += 1;
    for (size_t i = 0; i < line.size(); ++i) {
      if (line[i] != '0') {
        m_contents[i].insert(m_contents[i].begin(), line[i]);
      }
    }
    std::getline(p_input, line);
  }
  m_priority = calc_priority();
  m_stats->m_boards.insert(*this);
}

Board::Board(Board const& p_o, edge const& p_e)
  : m_contents(p_o.m_contents)
  , m_stats(p_o.m_stats)
  , m_id(m_stats->m_boards.size())
  , m_parent(&p_o)
  , m_distance(p_o.m_distance + 1) {
  apply(p_e);
}

Board::~Board() = default;

auto Board::is_solved() const -> bool {
  return std::ranges::all_of(m_contents,
                             [this](std::string const& p_s) { return p_s.empty() || is_full_and_homogeneous(p_s); });
}

auto Board::generate_steps() const -> std::vector<edge> {
  std::vector<edge> result;
  for (uint8_t i = 0; i < static_cast<uint8_t>(m_contents.size()); ++i) {
    for (uint8_t j = 0; j < static_cast<uint8_t>(m_contents.size()); ++j) {
      edge e{i, j};
      if (is_valid(e)) {
        result.push_back(e);
      }
    }
  }
  // std::cout << m_id << "\t: " << m_stats->m_boards.size() << "\t: " << result.size() << "\t: " << distance() << "\n";
  return result;
}

auto Board::operator+(edge const& p_e) const -> i_node const* {
  auto [b, is_new] = m_stats->m_boards.emplace(*this, p_e);
  if (is_new) {
    return std::to_address(b);
  }
  if (distance() + 1 < b->distance()) {
    b->m_parent = this;
    b->m_distance = m_distance + 1;
  }
  return nullptr;
}

void Board::print() const {
  //spdlog::info("\nd: {}, p(): {}", distance(), priority());
  const size_t height = m_stats->m_max_stack_height;
  for (size_t i = 0; i < height; ++i) {
    //tybl::log::log("\n");
    size_t r = (height - 1) - i;
    for (auto const& c : m_contents) {
      if (r < c.size()) {
        //tybl::log::log("{}", c.at(r));
      } else {
        //tybl::log::log(" ");
      }
    }
  }
}

auto Board::num_found() const -> size_t { return m_stats->m_boards.size(); }

void Board::print_steps() const {
  if (nullptr != m_parent) {
    m_parent->print_steps();
  }
  print();

  std::string ignore;
  std::getline(std::cin, ignore);
}

auto Board::priority() const -> size_t { return m_priority; }

auto Board::distance() const -> size_t { return m_distance; }

auto Board::operator<(Board const& p_o) const -> bool { return m_contents < p_o.m_contents; }

void Board::apply(edge const& p_e) {
  m_contents.at(p_e.stack_to).push_back(m_contents.at(p_e.stack_from).back());
  m_contents.at(p_e.stack_from).pop_back();
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

auto Board::count_suffix_matching(std::string_view p_s, char p_c) -> size_t {
  auto i = p_s.rbegin();
  while (i != p_s.rend() && *i == p_c) {
    ++i;
  }
  return static_cast<size_t>(std::distance(p_s.rbegin(), i));
}

auto Board::is_valid(edge const& p_e) const -> bool {
  if (p_e.stack_from == p_e.stack_to) {
    return false;
  }
  if (m_contents.at(p_e.stack_from).empty()) {
    return false;
  }
  if (is_full(m_contents.at(p_e.stack_to))) {
    return false;
  }
  if (is_full_and_homogeneous(m_contents[p_e.stack_from])) {
    return false;
  }
  if (m_contents.at(p_e.stack_to).empty()) {
    return true;
  }
  return m_contents[p_e.stack_to].back() == m_contents[p_e.stack_from].back();
}

auto Board::is_homogeneous(std::string const& p_s) -> bool {
  return std::ranges::all_of(p_s.begin(), p_s.end(), [&](char p_c) { return p_s.front() == p_c; });
}

auto Board::is_full(std::string_view p_s) const -> bool { return p_s.size() == m_stats->m_max_stack_height; }

auto Board::is_full_and_homogeneous(std::string const& p_s) const -> bool {
  return is_full(p_s) && is_homogeneous(p_s);
}
