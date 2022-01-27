// License: The Unlicense (https://unlicense.org)
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#define SET std::unordered_set

typedef unsigned __int128 uint128_t;

template <typename T>
class vector_set {
  std::vector<T> m_data;

public:
  vector_set() { m_data.reserve(226800); }
  size_t size() const { return m_data.size(); }
  bool contains(T const& t) const { return std::binary_search(m_data.begin(), m_data.end(), t); }
  void insert(T t) {
    auto i = std::upper_bound(m_data.begin(), m_data.end(), t);
    m_data.insert(i, t);
    if (!std::is_sorted(m_data.begin(), m_data.end())) {
      std::cout << "Not sorted\n";
    }
  }
#if 0
  template <typename I>
  void insert(I beg, I end) {
    std::sort(beg,end);
    auto i = m_data.insert(m_data.end(),beg,end);
    std::merge(m_data.begin(), i, i, m_data.end(), m_data.begin());
  }
#endif
};

class Node {
  std::vector<std::string> m_contents;
  size_t m_height;

public:
  size_t hex2uint(char c) const { return (c < 'A') ? c - '0' : c - 'A' + 0xA; }

  char uint2hex(size_t i) const { return (i < 9) ? '1' + i : 'A' + (i - 9); }

  Node(size_t h, size_t n)
    : m_contents(n + 2)
    , m_height(h) {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < h; ++j) {
        m_contents.at(i).push_back(uint2hex(i));
      }
    }
  }

  Node(Node const& o)
    : m_contents(o.m_contents)
    , m_height(o.m_height) {}

  auto get_next(SET<Node>& found) const -> std::vector<Node> {
    std::vector<Node> result;
    for (uint8_t i = 0; i < static_cast<uint8_t>(m_contents.size()); ++i) {
      for (uint8_t j = 0; j < static_cast<uint8_t>(m_contents.size()); ++j) {
        if (is_valid(i, j)) {
          Node newb(*this);
          newb.apply(i, j);
          if (!found.contains(newb)) {
            found.insert(newb);
            result.push_back(newb);
          }
        }
      }
    }
    return result;
  }

  auto operator<(Node const& o) const -> bool { return m_contents < o.m_contents; }

  size_t encode() const {
    std::cerr << "Encoding " << m_contents.size() << " stacks of height " << m_height << "\n";
    std::set<char> colors;
    for (auto const& s : m_contents) {
      for (auto const& c : s) {
        colors.insert(c);
      }
    }
    std::cerr << colors.size() << " colors\n";
    uint128_t result = 0;
    for (auto const& s : m_contents) {
      size_t digit = 0;
      for (auto const& c : s) {
        digit *= colors.size();
        digit += c;
      }
      uint128_t prev = result;
      result *= m_height * colors.size();
      result += digit;
      if (prev > result)
        std::cerr << "overflow\n";
    }
    return result;
  }

  void print(std::ostream& o) const {
    for (size_t i = 0; i < m_height; ++i) {
      o << '\n';
      size_t r = (m_height - 1) - i;
      for (auto const& c : m_contents) {
        if (r < c.size()) {
          o << c.at(r);
        } else {
          o << ' ';
        }
      }
    }
  }

private:
  void apply(uint8_t to, uint8_t from) {
    m_contents.at(to).push_back(m_contents.at(from).back());
    m_contents.at(from).pop_back();
  }
  bool is_valid(uint8_t to, uint8_t from) const {
    return (from != to) && (!m_contents.at(from).empty()) && (m_contents.at(to).size() != m_height);
  }

}; // class Node

size_t count_nodes(size_t height, size_t num_unique) {
  SET<Node> found(226800);
  std::vector<Node> queue{Node(height, num_unique)};
  found.insert(queue.back());
  // queue.back().print();
  // queue.back().encode();
  do {
    Node curr = queue.back();
    queue.pop_back();
    auto next = curr.get_next(found);
    // found.insert(next.begin(), next.end());
    queue.insert(queue.end(), next.begin(), next.end());
  } while (queue.size());
  return found.size();
}

auto main() -> int {
  for (size_t h = 1; h <= 3; ++h) {
    for (size_t n = 1; n <= 3; ++n) {
      count_nodes(h, n);
      std::cout << '(' << h << ',' << n << ") = " << count_nodes(h, n) << '\n';
    }
  }
}
