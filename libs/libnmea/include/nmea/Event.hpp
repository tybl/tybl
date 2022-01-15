// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_EVENT_HPP
#define TYBL_NMEA_EVENT_HPP

#include "nmea/EventHandler.hpp"

#include <functional>
#include <list>

namespace nmea {

template<class> class Event;
template<class> class EventHandler;

template <typename ... Args>
class Event<void(Args...)>
{
  friend EventHandler<void(Args...)>;
private:
  // Typenames
  typedef typename std::list<EventHandler<void(Args...)>>::iterator ListIterator;

  // Static members
  // (none)

  // Properties
  std::list<EventHandler<void(Args...)>> handlers;

  //Functions
  void copy(const Event& ref){
    if (&ref != this){
      handlers = ref.handlers;
    }
  };

  bool remove_handler(ListIterator handlerIter)  {
    if (handlerIter == handlers.end()){
      return false;
    }

    handlers.erase(handlerIter);
    return true;
  };

public:
  // Typenames
  // (none)

  // Static members
  // (none)

  // Properties
  bool enabled;

  // Functions
  Event() : enabled(true)
  {}

  virtual ~Event() 
  {}

  Event(const Event& ref)   {
    copy(ref);
  }

  void call(Args... args)  {
    if (!enabled) { return; }
    for (auto h = handlers.begin(); h != handlers.end(); h++)
    {
      (*h)(args...);
    }
  }

  EventHandler<void(Args...)> register_handler(EventHandler<void(Args...)> handler)  {
    bool found = false;
    for (auto h = handlers.begin(); h != handlers.end(); h++)
    {
      if ((*h) == handler)  {
        found = true;
        break;
      }
    }
    if (!found)
    {
      ListIterator itr = handlers.insert(handlers.end(), handler);
      handler._iterator = itr;
    }
    return handler;
  }

  EventHandler<void(Args...)> register_handler(std::function<void(Args...)> handler)  {
    EventHandler<void(Args...)> wrapper(handler);
    ListIterator itr = handlers.insert(handlers.end(), wrapper);
    wrapper._iterator = itr;
    return wrapper;
  }

  bool remove_handler(EventHandler<void(Args...)>& handler)  {
    bool sts = remove_handler(handler._iterator);
    handler._iterator = handlers.end();
    return sts;
  };

  void clear(){
    for (auto h = handlers.begin(); h != handlers.end(); h++)
    {
      (*h)._iterator = handlers.end();
    }
    handlers.clear();
  };

  void operator ()(Args... args) { return call(args...); };
  EventHandler<void(Args...)> operator +=(EventHandler<void(Args...)> handler)  { return register_handler(handler); };
  EventHandler<void(Args...)> operator +=(std::function<void(Args...)> handler)  { return register_handler(handler); };
  bool operator -=(EventHandler<void(Args...)>& handler)              { return remove_handler(handler); };
  bool operator -=(uint64_t handlerID) { return remove_handler(handlerID); };

  EventHandler<void(Args...)>& operator =(const EventHandler<void(Args...)>& ref){
    copy(ref);
    return *this;
  };

}; // class Event

} // namespace nmea

#endif // TYBL_NMEA_EVENT_HPP