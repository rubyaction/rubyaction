#ifndef __RUBY_ENGINE__
#define __RUBY_ENGINE__

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mruby/variable.h>

namespace RubyAction
{

  class RubyEngine
  {
  private:
    typedef void (*bindFunction)(mrb_state*, RClass*);
    static RubyEngine *instance;
    mrb_state *mrb;
    RClass *module;
    RubyEngine();

  public:
    ~RubyEngine();
    static RubyEngine* getInstance();
    void bind(bindFunction);
    bool load(const char *);
    void garbageCollect();
    mrb_state* getState();
    RClass* getClass(const char *);
    mrb_value newInstance(RClass *, mrb_value* = NULL, int = 0, bool = true);
    mrb_value newInstance(const char *, mrb_value* = NULL, int = 0, bool = true);
  };

}

#endif // __RUBY_ENGINE__
