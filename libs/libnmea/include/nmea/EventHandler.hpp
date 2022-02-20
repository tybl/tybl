// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_EVENTHANDLER_HPP
#define TYBL_NMEA_EVENTHANDLER_HPP

#include <cstdint>
#include <functional>
#include <utility>

namespace tybl::nmea {

template <class>
class Event;
template <class>
class EventHandler;

template <typename... Args>
class EventHandler<void(Args...)> {
  friend Event<void(Args...)>;
  // Typenames
  typename Event<void(Args...)>::ListIterator m_iterator;

  // Static members
  static uint64_t LastID;

  // Properties
  std::function<void(Args...)> m_handler;
  uint64_t m_id{};

public:
  // Typenames
  using CFunctionPointer = void (*)(Args...);

  // Functions
  EventHandler(std::function<void(Args...)> p_h)
    : m_iterator()
    , m_handler(std::move(p_h))
    , m_id(++LastID) {}

  void operator()(Args... p_args) { m_handler(p_args...); }

  auto operator==(const EventHandler& p_ref) -> bool { return m_id == p_ref.m_id; }

  auto operator!=(const EventHandler& p_ref) -> bool { return m_id != p_ref.m_id; }

  auto get_id() -> uint64_t { return m_id; }

  // Returns function pointer to the underlying function
  // or null if it's not a function but implements operator()
  auto get_function_pointer() -> CFunctionPointer* {
    return m_handler.template target<CFunctionPointer>();
    // CFunctionPointer* ptr = m_handler.template target<CFunctionPointer>();
    // return ptr;
  }

}; // class EventHandler

template <typename... Args>
uint64_t EventHandler<void(Args...)>::LastID = 0;

} // namespace tybl::nmea

#endif // TYBL_NMEA_EVENTHANDLER_HPP