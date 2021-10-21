// License: The Unlicense (https://unlicense.org)
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class Node {
  std::vector<std::string> m_contents;
  size_t m_height;
public:

  Node(size_t h, size_t n)
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

  Node(Node const& o)
    : m_contents(o.m_contents)
    , m_height(o.m_height)
  {}

  auto get_next(std::set<Node> const& found) const -> std::vector<Node> {
    std::vector<Node> result;
    for (uint8_t i = 0; i < static_cast<uint8_t>(m_contents.size()); ++i) {
      for (uint8_t j = 0; j < static_cast<uint8_t>(m_contents.size()); ++j) {
        if (is_valid(i,j)) {
          Node newb(*this);
          newb.apply(i,j);
          if (!found.contains(newb)) {
            result.push_back(newb);
          }
        }
      }
    }
    return result;
  }

  auto operator<(Node const& o) const -> bool {
    return m_contents < o.m_contents;
  }

  size_t hex2uint(char c) const {
    return (c < 'A') ? c - '0' : c - 'A' + 0xA;
  }

  size_t encode() const {
    std::cerr << "Encoding " << m_contents.size() << " stacks of height " << m_height << "\n";
    std::set<char> colors;
    for (auto const& s : m_contents) {
      for (auto const& c : s) {
        colors.insert(c);
      }
    }
    std::cerr << colors.size() << " colors\n";
    size_t result = 0;
    for (auto const& s : m_contents) {
      size_t digit = 0;
      for (auto const& c : s) {
        std::cerr << c << " " << std::hex << hex2uint(c) << '\n';
        digit *= colors.size();
        digit += c;
      }
      result *= m_height * colors.size();
      result += digit;
    }
    return result;
  }

  void print() const {
    for (size_t i = 0; i < m_height; ++i) {
      std::cout << '\n';
      size_t r = (m_height - 1) - i;
      for (auto const& c : m_contents) {
        if (r < c.size()) {
          std::cout << c.at(r);
        } else {
          std::cout << ' ';
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
  std::set<Node> found;
  std::vector<Node> queue { Node(height, num_unique) };
  found.insert(queue.back());
  queue.back().print();
  queue.back().encode();
  /*
  do {
    Node curr = queue.back();
    queue.pop_back();
    auto next = curr.get_next(found);
    found.insert(next.begin(), next.end());
    queue.insert(queue.end(), next.begin(), next.end());
  } while (queue.size());
  */
  return found.size();
}

auto main() -> int {
  for (size_t h = 1; h < 4; ++h) {
    for (size_t n = 1; n < 12; ++n) {
      count_nodes(h,n);
      //std::cout << '(' << h << ',' << n << ") = " << count_nodes(h,n) << '\n';
    }
  }
}
