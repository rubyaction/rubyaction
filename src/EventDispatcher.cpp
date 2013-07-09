#include "EventDispatcher.hpp"
#include "RubyEngine.hpp"

namespace RubyAction
{

  void EventDispatcher::on(mrb_sym name, RProc *listener)
  {
    listeners[name] = listener;
  }

  void EventDispatcher::off(mrb_sym name)
  {
    listeners.erase(name);
  }

  void EventDispatcher::off()
  {
    listeners.clear();
  }

  void EventDispatcher::dispatch(mrb_sym name, mrb_value arg)
  {
    RubyEngine::getInstance()->execute(listeners[name], arg);
  }

}

