#include "RubyEngine.hpp"

namespace RubyAction
{

  RubyEngine *RubyEngine::instance = new RubyEngine();

  RubyEngine* RubyEngine::getInstance()
  {
    return instance;
  }

  RubyEngine::RubyEngine()
  {
    mrb = mrb_open();
    module = mrb_define_module(mrb, "RubyAction");
  }

  RubyEngine::~RubyEngine()
  {
    mrb_close(mrb);
  }

  void RubyEngine::bind(bind_func func)
  {
    func(mrb, module);
  }

  bool RubyEngine::load(const char *filename)
  {
    bool loaded = true;
    mrbc_context *context = mrbc_context_new(mrb);

    struct mrb_parser_state *p = mrb_parse_file(mrb, fopen(filename, "r"), context);
    int n = mrb_generate_code(mrb, p);
    mrb_run(mrb, mrb_proc_new(mrb, mrb->irep[n]), mrb_top_self(mrb));
    if (mrb->exc) {
      mrb_p(mrb, mrb_obj_value(mrb->exc));
      loaded = false;
    }

    mrbc_context_free(mrb, context);
    this->garbageCollect();
    return loaded;
  }

  mrb_value RubyEngine::execute(RProc *proc, mrb_value arg)
  {
    return mrb_run(mrb, proc, arg);
  }

  void RubyEngine::garbageCollect()
  {
    mrb_garbage_collect(mrb);
  }

  mrb_state* RubyEngine::getState()
  {
    return mrb;
  }

}

