// License: The Unlicense (https://unlicense.org)

#include "server.hpp"

#include "nlohmann/json.hpp"

#include <boost/asio.hpp>

#include <chrono>
#include <iostream> // cout
#include <string>

using boost::asio::ip::udp;

server::server(boost::asio::io_service& io_service, uint16_t port)
  : m_socket(io_service, udp::endpoint(udp::v4(), port))
{
  do_receive();
}

void server::do_receive() {
  auto rx_response = [this](boost::system::error_code ec, std::size_t bytes_recvd) {
    if (!ec && bytes_recvd > 0) {
      auto sensor_data = nlohmann::json::parse(std::string(m_data.data(), bytes_recvd));
      const auto n = std::chrono::system_clock::now();
      std::cout << std::chrono::duration_cast<std::chrono::seconds>(n.time_since_epoch()).count()
                << ": From: \"" << m_sender_endpoint << "\", received: \""
                << sensor_data.dump() << "\"\n";
    }
    do_receive();
  };
  m_socket.async_receive_from(boost::asio::buffer(m_data, m_data.size()), m_sender_endpoint, rx_response);
}
