#include "Executor.hpp"

#include <chrono>
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
      std::cout << "Took " << elapsed_seconds.count() << "s to solve\n";
      solution->print_steps();
    }
  }
}
