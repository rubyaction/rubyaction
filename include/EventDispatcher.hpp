#ifndef __EVENT_DISPATCHER__
#define __EVENT_DISPATCHER__

#include "RubyObject.hpp"
#include <mruby.h>


namespace RubyAction
{

  class EventDispatcher : public RubyObject
  {
  public:
    EventDispatcher(mrb_value);
    void on(mrb_sym, mrb_value);
    void off(mrb_sym);
    void off();
    void dispatch(mrb_sym, mrb_value*, int);
  };

  void bindEventDispatcher(mrb_state*, RClass*);

}

#endif // __EVENT_DISPATCHER__
