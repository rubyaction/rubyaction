#ifndef __RUBY_ACTION_WRAPPER_HPP__
#define __RUBY_ACTION_WRAPPER_HPP__

#include "RubyObject.hpp"

namespace RubyAction
{

  struct RubyObjectWrapper
  {
    RubyObjectWrapper(RubyObject* object) : instance(object) {}
    RubyObject *instance;
  };

  static void freeRubyObject(mrb_state* mrb, void* pointer)
  {
    RubyObjectWrapper *wrapper = (RubyObjectWrapper*) pointer;
    if (wrapper && wrapper->instance)
    {
      delete wrapper->instance;
      wrapper->instance = NULL;
    }
    mrb_free(mrb, wrapper);
  }

  const struct mrb_data_type RubyObjectBinding = { "RubyObject", freeRubyObject };

  static void wrap(mrb_value value, RubyObject* object)
  {
    RubyObjectWrapper *wrapper = (RubyObjectWrapper*) DATA_PTR(value);
    if (wrapper) freeRubyObject(RubyEngine::getInstance()->getState(), wrapper);
    DATA_PTR(value) = new RubyObjectWrapper(object);
    DATA_TYPE(value) = &RubyObjectBinding;
  }

  template<typename T>
  static T* unwrap(mrb_value value)
  {
    return (T*) ((RubyObjectWrapper*) DATA_PTR(value))->instance;
  }

}

#endif // __RUBY_ACTION_WRAPPER_HPP__
