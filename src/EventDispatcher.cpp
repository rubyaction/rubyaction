#include "EventDispatcher.hpp"
#include "RubyEngine.hpp"

namespace RubyAction
{

  EventDispatcher::EventDispatcher(mrb_value self)
    : RubyObject(self)
  {
  }

  void EventDispatcher::on(mrb_sym name, mrb_value listener)
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

  void EventDispatcher::dispatch(mrb_sym name, mrb_value data)
  {
    if (listeners.count(name))
    {
      mrb_value listener = listeners[name];
      mrb_state *mrb = RubyEngine::getInstance()->getState();

      if (mrb_symbol_p(listener))
        mrb_funcall_argv(mrb, self, mrb_symbol(listener), 1, &data);
      else
        mrb_yield(mrb, listener, data);
    }
  }

  static mrb_value EventDispatcher_initialize(mrb_state *mrb, mrb_value self)
  {
    SET_INSTANCE(new EventDispatcher(self))
    return self;
  }

  static mrb_value EventDispatcher_on(mrb_state *mrb, mrb_value self)
  {
    mrb_sym name;
    mrb_sym method;
    mrb_value listener;
    int argc = mrb_get_args(mrb, "n|n&", &name, &method, &listener);

    if (argc == 2) listener = mrb_symbol_value(method);

    GET_INSTANCE(EventDispatcher)
    instance->on(name, listener);

    return self;
  }

  static mrb_value EventDispatcher_off(mrb_state *mrb, mrb_value self)
  {
    mrb_sym name;
    int argc = mrb_get_args(mrb, "|n", &name);

    GET_INSTANCE(EventDispatcher)

    if (argc == 0)
      instance->off();
    else
      instance->off(name);

    return self;
  }

  static mrb_value EventDispatcher_dispatch(mrb_state *mrb, mrb_value self)
  {
    mrb_sym name;
    mrb_value data;
    int argc = mrb_get_args(mrb, "n|o", &name, &data);

    if (argc == 1) data = mrb_nil_value();

    GET_INSTANCE(EventDispatcher)
    instance->dispatch(name, data);

    return self;
  }

  void bindEventDispatcher(mrb_state *mrb, RClass *module)
  {
    struct RClass *clazz = mrb_define_class_under(mrb, module, "EventDispatcher", mrb->object_class);
    MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

    mrb_define_method(mrb, clazz, "initialize", EventDispatcher_initialize, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "on", EventDispatcher_on, MRB_ARGS_ARG(1, 1));
    mrb_define_method(mrb, clazz, "off", EventDispatcher_off, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, clazz, "dispatch", EventDispatcher_dispatch, MRB_ARGS_ARG(1, 1));
  }

}

