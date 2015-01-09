#ifndef __RUBY_OBJECT__
#define __RUBY_OBJECT__

#include "RubyEngine.hpp"

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
    static int instances;
    mrb_value getProperty(const char *);
    void setProperty(const char *, mrb_value);
    RubyObject* getObject(const char *);
    void setSelf(mrb_value);
    mrb_value getSelf();
  };

}

#include "util/wrapper.hpp"

#endif // __RUBY_OBJECT__
