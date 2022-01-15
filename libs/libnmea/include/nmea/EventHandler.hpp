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
  typename Event<void(Args...)>::ListIterator _iterator;

  // Static members
  static uint64_t LastID;

  // Properties
  std::function<void(Args...)> handler;
  uint64_t ID;

  // Functions
  void copy(const EventHandler& ref){
    if (&ref != this){
      _iterator = ref._iterator;
      handler = ref.handler;
      ID = ref.ID;
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
  EventHandler(std::function<void(Args...)> h) : _iterator(), handler(h), ID(++LastID)
  {}

  EventHandler(const EventHandler& ref){
    copy(ref);
  }

  virtual ~EventHandler(){};

  EventHandler& operator=(const EventHandler& ref){
    copy(ref);
    return *this;
  }

  void operator() (Args... args){
    handler(args...);
  }

  bool operator==(const EventHandler& ref){
    return ID == ref.ID;
  }

  bool operator!=(const EventHandler& ref){
    return ID != ref.ID;
  }

  uint64_t get_id(){
    return ID;
  }

  // Returns function pointer to the underlying function
  // or null if it's not a function but implements operator()
  CFunctionPointer* get_function_pointer(){
    CFunctionPointer* ptr = handler.template target<CFunctionPointer>();
    return ptr;
  }

}; // class EventHandler

template<typename... Args>
uint64_t EventHandler<void(Args...)>::LastID = 0;

} // namespace nmea

#endif // TYBL_NMEA_EVENTHANDLER_HPP