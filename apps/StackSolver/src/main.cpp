// License: The Unlicense (https://unlicense.org)
#include "executor.hpp"
#include "graph/a_star_search.hpp"
#include "stacksolve/stack_state.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>

auto main(int argc, char const* argv[]) -> int {
  if (2 == argc) {
    std::ifstream input(argv[1]);
    executor e(input);
    tybl::stacksolve::stack_state start_node(tybl::vodka::dynarray_2d<char>(5, 9));
    tybl::graph::a_star_search<tybl::stacksolve::stack_state> astar(start_node);
    auto start = std::chrono::high_resolution_clock::now();
    auto const* solution_p = e.solve();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    if (nullptr != solution_p) {
      std::cout << std::fixed << std::setprecision(8) << elapsed_seconds.count() << "," << solution_p->num_found()
                << "\n";
      solution_p->print_steps();
    }
  }
}
