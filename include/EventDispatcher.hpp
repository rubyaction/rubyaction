#ifndef __EVENT_DISPATCHER__
#define __EVENT_DISPATCHER__

#include "RubyObject.hpp"

namespace RubyAction
{

  class EventDispatcher : public RubyObject
  {
  public:
    EventDispatcher(mrb_value);
    void on(mrb_sym, mrb_value);
    void off(mrb_sym);
    void off();
    virtual void dispatch(mrb_sym, mrb_value* = NULL, int = 0);
  };

  void bindEventDispatcher(mrb_state*, RClass*);

}

#endif // __EVENT_DISPATCHER__
