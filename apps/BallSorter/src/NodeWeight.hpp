// License: The Unlicense (https://unlicense.org)
#ifndef NODEWEIGHT_HPP
#define NODEWEIGHT_HPP

#include "INode.hpp"

struct NodeWeight {

  bool operator () (INode const* lhs, INode const* rhs) {
    auto lp = lhs->priority();
    auto rp = rhs->priority();
    return (lp < rp) || (lp == rp && lhs->distance() > rhs->distance());
  }

}; // struct NodeWeight

#endif // NODEWEIGHT_HPP
