#include "Executor.hpp"

#include <chrono>
#include <iostream>

int main(int argc, char const* argv[]) {
  if (2 == argc) {
    std::ifstream input(argv[1]);
    Executor e(input);
    auto start = std::chrono::high_resolution_clock::now();
    auto solution = e.solve();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if (solution) {
      std::cout << "Took " << elapsed_seconds.count() << "s to solve\n";
      solution->print_steps();
    }
  }
}
