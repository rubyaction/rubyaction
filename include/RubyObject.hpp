#ifndef __RUBY_OBJECT__
#define __RUBY_OBJECT__

#include "RubyEngine.hpp"
#include <stddef.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mruby/variable.h>

namespace RubyAction
{

  class RubyObject
  {
  protected:
    mrb_value self;
    mrb_state *mrb;
    RubyObject(mrb_value self);
  public:
    virtual ~RubyObject();
    const char * inspect();
    mrb_value getProperty(const char *);
    void setProperty(const char *, mrb_value);
    RubyObject* getObject(const char *);
    void setSelf(mrb_value self) { this->self = self; };
    mrb_value getSelf() { return self; };
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

#define SET_INSTANCE(value, object) \
  { mrb_ruby_object_type *wrapper = (mrb_ruby_object_type *) mrb_check_datatype(mrb, value, &mrb_ruby_object_binding); \
  if (wrapper) mrb_ruby_object_free(mrb, wrapper); \
  wrapper = new mrb_ruby_object_type; \
  wrapper->instance = object; \
  DATA_PTR(value) = wrapper; \
  DATA_TYPE(value) = &mrb_ruby_object_binding; }

#define GET_INSTANCE(value, variable, type) \
  type *variable; \
  { mrb_ruby_object_type *wrapper = (mrb_ruby_object_type *) mrb_check_datatype(mrb, value, &mrb_ruby_object_binding); \
  variable = (type*) wrapper->instance; }

}

#endif // __RUBY_OBJECT__
