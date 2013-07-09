#ifndef __EVENT_DISPATCHER__
#define __EVENT_DISPATCHER__

#include <map>
#include <mruby.h>

namespace RubyAction
{

  class EventDispatcher
  {
  private:
    std::map<mrb_sym, RProc*> listeners;
  public:
    void on(mrb_sym, RProc*);
    void off(mrb_sym);
    void off();
    void dispatch(mrb_sym, mrb_value);
  };

}

#endif // __EVENT_DISPATCHER__

