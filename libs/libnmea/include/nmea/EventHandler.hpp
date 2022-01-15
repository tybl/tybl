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
  void copy(const EventHandler& ref){
    if (&ref != this){
      m_iterator = ref.m_iterator;
      m_handler = ref.m_handler;
      m_id = ref.m_id;
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
  EventHandler(std::function<void(Args...)> h) : m_iterator(), m_handler(h), m_id(++LastID)
  {}

  EventHandler(const EventHandler& ref){
    copy(ref);
  }

  virtual ~EventHandler(){};

  EventHandler& operator=(const EventHandler& ref){
    copy(ref);
    return *this;
  }

  void operator() (Args... args){ m_handler(args...);
  }

  bool operator==(const EventHandler& ref){
    return m_id == ref.m_id;
  }

  bool operator!=(const EventHandler& ref){
    return m_id != ref.m_id;
  }

  uint64_t get_id(){
    return m_id;
  }

  // Returns function pointer to the underlying function
  // or null if it's not a function but implements operator()
  CFunctionPointer* get_function_pointer(){
    CFunctionPointer* ptr = m_handler.template target<CFunctionPointer>();
    return ptr;
  }

}; // class EventHandler

template<typename... Args>
uint64_t EventHandler<void(Args...)>::LastID = 0;

} // namespace nmea

#endif // TYBL_NMEA_EVENTHANDLER_HPP