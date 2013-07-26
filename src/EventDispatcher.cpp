#include "EventDispatcher.hpp"
#include "RubyEngine.hpp"
#include <mruby/hash.h>

namespace RubyAction
{

  EventDispatcher::EventDispatcher(mrb_value self)
    : RubyObject(self)
  {
    if (!mrb_nil_p(self))
    {
      setProperty("listeners", mrb_hash_new(mrb));
    }
  }

  void EventDispatcher::on(mrb_sym name, mrb_value listener)
  {
    mrb_hash_set(mrb, getProperty("listeners"), mrb_symbol_value(name), listener);
  }

  void EventDispatcher::off(mrb_sym name)
  {
    mrb_hash_delete_key(mrb, getProperty("listeners"), mrb_symbol_value(name));
  }

  void EventDispatcher::off()
  {
    setProperty("listeners", mrb_hash_new(mrb));
  }

  void EventDispatcher::dispatch(mrb_sym name, mrb_value* argv, int argc)
  {
    mrb_value listener = mrb_hash_get(mrb, getProperty("listeners"), mrb_symbol_value(name));
    if (!mrb_nil_p(listener))
    {
      if (mrb_symbol_p(listener))
        mrb_funcall_argv(mrb, self, mrb_symbol(listener), argc, argv);
      else
        mrb_yield_argv(mrb, listener, argc, argv);
    }
  }

  static mrb_value EventDispatcher_initialize(mrb_state *mrb, mrb_value self)
  {
    SET_INSTANCE(self, new EventDispatcher(self))
    return self;
  }

  static mrb_value EventDispatcher_on(mrb_state *mrb, mrb_value self)
  {
    mrb_sym name;
    mrb_sym method;
    mrb_value listener;
    int argc = mrb_get_args(mrb, "n|n&", &name, &method, &listener);

    if (argc == 2) listener = mrb_symbol_value(method);

    GET_INSTANCE(self, dispatcher, EventDispatcher)
    dispatcher->on(name, listener);

    return self;
  }

  static mrb_value EventDispatcher_off(mrb_state *mrb, mrb_value self)
  {
    mrb_sym name;
    int argc = mrb_get_args(mrb, "|n", &name);

    GET_INSTANCE(self, dispatcher, EventDispatcher)

    if (argc == 0)
      dispatcher->off();
    else
      dispatcher->off(name);

    return self;
  }

  static mrb_value EventDispatcher_dispatch(mrb_state *mrb, mrb_value self)
  {
    mrb_sym name;
    mrb_value *argv;
    int argc;
    mrb_get_args(mrb, "n*", &name, &argv, &argc);

    GET_INSTANCE(self, dispatcher, EventDispatcher)
    dispatcher->dispatch(name, argv, argc);

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

