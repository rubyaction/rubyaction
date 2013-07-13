#ifndef __EVENT_DISPATCHER__
#define __EVENT_DISPATCHER__

#include "RubyObject.hpp"
#include <map>
#include <mruby.h>
#include <mruby/value.h>
#include <mruby/proc.h>

namespace RubyAction
{

  class EventDispatcher : public RubyObject
  {
  private:
    std::map<mrb_sym, mrb_value> listeners;
  public:
    EventDispatcher(mrb_value);
    void on(mrb_sym, mrb_value);
    void off(mrb_sym);
    void off();
    void dispatch(mrb_sym, mrb_value);
  };

  void bindEventDispatcher(mrb_state*, RClass*);

}

#endif // __EVENT_DISPATCHER__

