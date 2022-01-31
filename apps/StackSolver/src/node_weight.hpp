// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_STACKSOLVER_NODEWEIGHT_HPP
#define TYBL_STACKSOLVER_NODEWEIGHT_HPP

#include "i_node.hpp"

struct node_weight {

  auto operator()(i_node const* p_lhs, i_node const* p_rhs) const -> bool {
    auto lp = p_lhs->priority();
    auto rp = p_rhs->priority();
    return (lp < rp) || (lp == rp && p_lhs->distance() > p_rhs->distance());
  }

}; // struct node_weight

#endif // TYBL_STACKSOLVER_NODEWEIGHT_HPP
