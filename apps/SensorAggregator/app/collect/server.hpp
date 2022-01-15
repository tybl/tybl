// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef SENSORAGGREGATOR_COLLECT_SERVER_HPP
#define SENSORAGGREGATOR_COLLECT_SERVER_HPP

#include <boost/asio.hpp>

#include <array>

class server {
  boost::asio::ip::udp::socket m_socket;
  boost::asio::ip::udp::endpoint m_sender_endpoint;
  std::array<char, 1024> m_data;

public:

  server(boost::asio::io_service& io_service, uint16_t port);

  void do_receive();

}; // class server

#endif // SENSORAGGREGATOR_COLLECT_SERVER_HPP
