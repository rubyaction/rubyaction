#ifndef __RUBY_OBJECT__
#define __RUBY_OBJECT__

#include "RubyEngine.hpp"
#include <stddef.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>

namespace RubyAction
{

  class RubyObject
  {
  protected:
    mrb_value self;
    RubyObject(mrb_value self);
  public:
    virtual ~RubyObject();
    const char * inspect();
  };

  struct mrb_ruby_object_type
  {
    mrb_ruby_object_type() : instance(NULL) {}
    RubyObject *instance;
  };

  static void mrb_ruby_object_free(mrb_state *mrb, void *pointer)
  {
    mrb_ruby_object_type *wrapper = (mrb_ruby_object_type *) pointer;
    if (wrapper && wrapper->instance)
    {
      delete wrapper->instance;
      wrapper->instance = NULL;
    }
    mrb_free(mrb, wrapper);
  }

  extern struct mrb_data_type mrb_ruby_object_binding;

#define SET_INSTANCE(value) \
  mrb_ruby_object_type *wrapper = (mrb_ruby_object_type *) mrb_check_datatype(mrb, self, &mrb_ruby_object_binding); \
  if (wrapper) mrb_ruby_object_free(mrb, wrapper); \
  wrapper = new mrb_ruby_object_type; \
  wrapper->instance = value; \
  DATA_PTR(self) = wrapper; \
  DATA_TYPE(self) = &mrb_ruby_object_binding;

#define GET_INSTANCE(type) \
  mrb_ruby_object_type *wrapper = (mrb_ruby_object_type *) mrb_check_datatype(mrb, self, &mrb_ruby_object_binding); \
  if (!wrapper || !wrapper->instance) return self; \
  type *instance = (type*) wrapper->instance;

}

#endif // __RUBY_OBJECT__
