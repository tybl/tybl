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
  std::list<EventHandler<void(Args...)>> m_handlers;

  //Functions
  void copy(const Event& ref){
    if (&ref != this){
      m_handlers = ref.m_handlers;
    }
  };

  bool remove_handler(ListIterator handlerIter)  {
    if (handlerIter == m_handlers.end()){
      return false;
    }

    m_handlers.erase(handlerIter);
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
    for (auto h = m_handlers.begin(); h != m_handlers.end(); h++)
    {
      (*h)(args...);
    }
  }

  EventHandler<void(Args...)> register_handler(EventHandler<void(Args...)> handler)  {
    bool found = false;
    for (auto h = m_handlers.begin(); h != m_handlers.end(); h++)
    {
      if ((*h) == handler)  {
        found = true;
        break;
      }
    }
    if (!found)
    {
      ListIterator itr = m_handlers.insert(m_handlers.end(), handler);
      handler.m_iterator = itr;
    }
    return handler;
  }

  EventHandler<void(Args...)> register_handler(std::function<void(Args...)> handler)  {
    EventHandler<void(Args...)> wrapper(handler);
    ListIterator itr = m_handlers.insert(m_handlers.end(), wrapper);
    wrapper.m_iterator = itr;
    return wrapper;
  }

  bool remove_handler(EventHandler<void(Args...)>& handler)  {
    bool sts = remove_handler(handler.m_iterator);
    handler.m_iterator = m_handlers.end();
    return sts;
  };

  void clear(){
    for (auto h = m_handlers.begin(); h != m_handlers.end(); h++)
    {
      (*h).m_iterator = m_handlers.end();
    }
    m_handlers.clear();
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