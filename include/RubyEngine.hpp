#ifndef __RUBY_ENGINE__
#define __RUBY_ENGINE__

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>

namespace RubyAction
{

  class RubyEngine
  {
  private:
    typedef void (*bind_func)(mrb_state*, RClass*);
    static RubyEngine *instance;
    mrb_state *mrb;
    RClass *module;
    RubyEngine();

  public:
    ~RubyEngine();
    static RubyEngine* getInstance();
    void bind(bind_func);
    bool load(const char*);
    void garbageCollect();
    mrb_state* getState();
  };

}

#endif // __RUBY_ENGINE__
