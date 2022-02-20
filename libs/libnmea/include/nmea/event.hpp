// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_EVENT_HPP
#define TYBL_NMEA_EVENT_HPP

#include <nmea/event_handler.hpp>

#include <functional>
#include <list>

namespace tybl::nmea {

template <class>
class Event;

template <class>
class EventHandler;

template <typename... Args>
class Event<void(Args...)> {
  friend EventHandler<void(Args...)>;

  using ListIterator = typename std::list<EventHandler<void(Args...)>>::iterator;

  std::list<EventHandler<void(Args...)>> m_handlers;

  auto remove_handler(ListIterator p_handler_i) -> bool {
    if (p_handler_i == m_handlers.end()) {
      return false;
    }

    m_handlers.erase(p_handler_i);
    return true;
  }

public:
  bool enabled = true;

  void call(Args... p_args) {
    if (!enabled) {
      return;
    }
    for (auto h = m_handlers.begin(); h != m_handlers.end(); h++) {
      (*h)(p_args...);
    }
  }

  auto register_handler(EventHandler<void(Args...)> p_handler) -> EventHandler<void(Args...)> {
    bool found = false;
    for (auto h = m_handlers.begin(); h != m_handlers.end(); h++) {
      if ((*h) == p_handler) {
        found = true;
        break;
      }
    }
    if (!found) {
      ListIterator itr = m_handlers.insert(m_handlers.end(), p_handler);
      p_handler.m_iterator = itr;
    }
    return p_handler;
  }

  auto register_handler(std::function<void(Args...)> p_handler) -> EventHandler<void(Args...)> {
    EventHandler<void(Args...)> wrapper(p_handler);
    auto itr = m_handlers.insert(m_handlers.end(), wrapper);
    wrapper.m_iterator = itr;
    return wrapper;
  }

  auto remove_handler(EventHandler<void(Args...)>& p_handler) -> bool {
    bool sts = remove_handler(p_handler.m_iterator);
    p_handler.m_iterator = m_handlers.end();
    return sts;
  }

  void clear() {
    for (auto h = m_handlers.begin(); h != m_handlers.end(); h++) {
      (*h).m_iterator = m_handlers.end();
    }
    m_handlers.clear();
  }

  void operator()(Args... p_args) { return call(p_args...); };

  auto operator+=(EventHandler<void(Args...)> p_handler) -> EventHandler<void(Args...)> {
    return register_handler(p_handler);
  }

  auto operator+=(std::function<void(Args...)> p_handler) -> EventHandler<void(Args...)> {
    return register_handler(p_handler);
  }

  auto operator-=(EventHandler<void(Args...)>& p_handler) -> bool { return remove_handler(p_handler); };

  auto operator-=(uint64_t p_handler_id) -> bool { return remove_handler(p_handler_id); };

}; // class Event

} // namespace tybl::nmea

#endif // TYBL_NMEA_EVENT_HPP
