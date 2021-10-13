// License: The Unlicense (https://unlicense.org)
#include "AStarSearch.hpp"
#include "Executor.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>

auto main(int argc, char const* argv[]) -> int {
  if (2 == argc) {
    std::ifstream input(argv[1]);
    Executor e(input);
    auto start = std::chrono::high_resolution_clock::now();
    auto const* solution = e.solve();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if (nullptr != solution) {
      std::cout << std::fixed << std::setprecision(8) << elapsed_seconds.count()
                << "," << solution->num_found() << "\n";
      solution->print_steps();
    }
  }
}
