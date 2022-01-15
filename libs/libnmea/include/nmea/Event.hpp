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
  void copy(const Event& p_ref){
    if (&p_ref != this){
      m_handlers = p_ref.m_handlers;
    }
  };

  bool remove_handler(ListIterator p_handler_i)  {
    if (p_handler_i == m_handlers.end()){
      return false;
    }

    m_handlers.erase(p_handler_i);
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

  Event(const Event& p_ref)   {
    copy(p_ref);
  }

  void call(Args... p_args)  {
    if (!enabled) { return; }
    for (auto h = m_handlers.begin(); h != m_handlers.end(); h++)
    {
      (*h)(p_args...);
    }
  }

  EventHandler<void(Args...)> register_handler(EventHandler<void(Args...)> p_handler)  {
    bool found = false;
    for (auto h = m_handlers.begin(); h != m_handlers.end(); h++)
    {
      if ((*h) == p_handler)  {
        found = true;
        break;
      }
    }
    if (!found)
    {
      ListIterator itr = m_handlers.insert(m_handlers.end(), p_handler);
      p_handler.m_iterator = itr;
    }
    return p_handler;
  }

  EventHandler<void(Args...)> register_handler(std::function<void(Args...)> p_handler)  {
    EventHandler<void(Args...)> wrapper(p_handler);
    ListIterator itr = m_handlers.insert(m_handlers.end(), wrapper);
    wrapper.m_iterator = itr;
    return wrapper;
  }

  bool remove_handler(EventHandler<void(Args...)>& p_handler)  {
    bool sts = remove_handler(p_handler.m_iterator);
    p_handler.m_iterator = m_handlers.end();
    return sts;
  };

  void clear(){
    for (auto h = m_handlers.begin(); h != m_handlers.end(); h++)
    {
      (*h).m_iterator = m_handlers.end();
    }
    m_handlers.clear();
  };

  void operator ()(Args... p_args) { return call(p_args...); };
  EventHandler<void(Args...)> operator +=(EventHandler<void(Args...)> p_handler)  { return register_handler(p_handler); };
  EventHandler<void(Args...)> operator +=(std::function<void(Args...)> p_handler)  { return register_handler(p_handler); };
  bool operator -=(EventHandler<void(Args...)>& p_handler)              { return remove_handler(p_handler); };
  bool operator -=(uint64_t p_handler_id) { return remove_handler(p_handler_id); };

  EventHandler<void(Args...)>& operator =(const EventHandler<void(Args...)>& p_ref){
    copy(p_ref);
    return *this;
  };

}; // class Event

} // namespace nmea

#endif // TYBL_NMEA_EVENT_HPP