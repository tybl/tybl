// License: The Unlicense (https://unlicense.org)
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

struct Edge {
  uint8_t StackFrom;
  uint8_t StackTo;
}; // struct Edge

class Board {
  std::vector<std::string> m_contents;
  size_t m_height;
public:

  Board(size_t h, size_t n)
    : m_contents(n + 2)
    , m_height(h)
  {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < h; ++j) {
        char c = (i < 9) ? '1' + i : 'A' + (i - 9);
        m_contents.at(i).push_back(c);
      }
    }
  }

  Board(Board const& o)
    : m_contents(o.m_contents)
    , m_height(o.m_height)
  {}

  auto is_solved() const -> bool {
    return std::ranges::all_of(m_contents, [this](std::string const& s) {
      return s.empty() || is_full_and_homogeneous(s);
    });
  }

  auto get_next(std::set<Board> const& found) const -> std::vector<Board> {
    std::vector<Board> result;
    for (uint8_t i = 0; i < static_cast<uint8_t>(m_contents.size()); ++i) {
      for (uint8_t j = 0; j < static_cast<uint8_t>(m_contents.size()); ++j) {
        if (is_valid(i,j)) {
          Board newb(*this);
          newb.apply(i,j);
          if (!found.contains(newb)) {
            result.push_back(newb);
          }
        }
      }
    }
    return result;
  }

  auto operator<(Board const& o) const -> bool {
    return m_contents < o.m_contents;
  }

private:

  void apply(uint8_t to, uint8_t from) {
    m_contents.at(to).push_back(m_contents.at(from).back());
    m_contents.at(from).pop_back();
  }
  bool is_full(std::string const& s) const {
    return s.size() == m_height;
  }
  bool is_full_and_homogeneous(std::string const& s) const {
    return is_full(s) && is_homogeneous(s);
  }
  static auto is_homogeneous(std::string const& s) -> bool {
    return std::all_of(s.begin(), s.end(), [&](char c){ return s.front() == c; });
  }
  bool is_valid(uint8_t to, uint8_t from) const {
    return (from != to) && (!m_contents.at(from).empty()) && (!is_full(m_contents.at(to)));
  }

}; // class Board

size_t count_nodes(size_t height, size_t num_unique) {
  std::set<Board> found;
  std::vector<Board> queue { Board(height, num_unique) };
  found.insert(queue.back());
  do {
    Board curr = queue.back();
    queue.pop_back();
    auto next = curr.get_next(found);
    found.insert(next.begin(), next.end());
    queue.insert(queue.end(), next.begin(), next.end());
  } while (queue.size());
  return found.size();
}

auto main() -> int {
  for (size_t h = 1; h < 4; ++h) {
    for (size_t n = 1; n < 5; ++n) {
      std::cout << '(' << h << ',' << n << ") = " << count_nodes(h,n) << '\n';
    }
  }
}
