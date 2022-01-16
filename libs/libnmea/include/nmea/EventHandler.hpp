// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_EVENTHANDLER_HPP
#define TYBL_NMEA_EVENTHANDLER_HPP

#include <cstdint>
#include <functional>

namespace nmea {

template<class> class Event;
template<class> class EventHandler;

template<typename... Args>
class EventHandler<void(Args...)>
{
  friend Event<void(Args...)>;
private:
  // Typenames
  typename Event<void(Args...)>::ListIterator m_iterator;

  // Static members
  static uint64_t LastID;

  // Properties
  std::function<void(Args...)> m_handler;
  uint64_t m_id;

  // Functions
  void copy(const EventHandler& p_ref){
    if (&p_ref != this){
      m_iterator = p_ref.m_iterator;
      m_handler = p_ref.m_handler;
      m_id = p_ref.m_id;
    }
  }

public:
  // Typenames
  typedef void(*CFunctionPointer)(Args...);

  // Static members
  // (none)

  // Properties
  // (none)

  // Functions
  EventHandler(std::function<void(Args...)> p_h) : m_iterator(), m_handler(p_h), m_id(++LastID)
  {}

  EventHandler(const EventHandler& p_ref){
    copy(p_ref);
  }

  virtual ~EventHandler(){};

  EventHandler& operator=(const EventHandler& p_ref){
    copy(p_ref);
    return *this;
  }

  void operator() (Args... p_args){ m_handler(p_args...);
  }

  bool operator==(const EventHandler& p_ref){
    return m_id == p_ref.m_id;
  }

  bool operator!=(const EventHandler& p_ref){
    return m_id != p_ref.m_id;
  }

  uint64_t get_id(){
    return m_id;
  }

  // Returns function pointer to the underlying function
  // or null if it's not a function but implements operator()
  CFunctionPointer* get_function_pointer(){
    return m_handler.template target<CFunctionPointer>();
    //CFunctionPointer* ptr = m_handler.template target<CFunctionPointer>();
    //return ptr;
  }

}; // class EventHandler

template<typename... Args>
uint64_t EventHandler<void(Args...)>::LastID = 0;

} // namespace nmea

#endif // TYBL_NMEA_EVENTHANDLER_HPP