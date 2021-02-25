// License: The Unlicense (https://unlicense.org)

#include "server.hpp"

#include <boost/asio.hpp>

#include <cstdlib>
#include <iostream> // cerr

auto main(int argc, char* argv[]) -> int {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <port>\n";
    return 1;
  }
  try {
    boost::asio::io_service io_service;
    server s(io_service, static_cast<uint16_t>(std::atoi(argv[1])));
    io_service.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
