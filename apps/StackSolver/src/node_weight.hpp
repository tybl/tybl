// License: The Unlicense (https://unlicense.org)
#ifndef NODEWEIGHT_HPP
#define NODEWEIGHT_HPP

#include "i_node.hpp"

struct node_weight {

  bool operator () (i_node const* lhs, i_node const* rhs) {
    auto lp = lhs->priority();
    auto rp = rhs->priority();
    return (lp < rp) || (lp == rp && lhs->distance() > rhs->distance());
  }

}; // struct node_weight

#endif // NODEWEIGHT_HPP
