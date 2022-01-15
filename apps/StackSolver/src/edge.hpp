// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_STACKSOLVER_EDGE_HPP
#define TYBL_STACKSOLVER_EDGE_HPP

#include <cstdint>

struct edge {
  uint8_t stack_from;
  uint8_t stack_to;
}; // struct edge

#endif // TYBL_STACKSOLVER_EDGE_HPP
