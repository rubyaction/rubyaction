#include "RubyEngine.hpp"
#include "mruby/class.h"
#include "mruby/variable.h"

using namespace RubyAction;

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
  struct RProc *proc = mrb_generate_code(mrb, p);
  mrb_run(mrb, proc, mrb_top_self(mrb));
  if (mrb->exc) {
    mrb_p(mrb, mrb_obj_value(mrb->exc));
    loaded = false;
  }

  mrbc_context_free(mrb, context);
  this->garbageCollect();
  return loaded;
}

void RubyEngine::garbageCollect()
{
  mrb_garbage_collect(mrb);
}

mrb_state* RubyEngine::getState()
{
  return mrb;
}

RClass* RubyEngine::getClass(const char *name)
{
  return mrb_class_get_under(mrb, module, name);
}

mrb_value RubyEngine::newInstance(RClass* clazz, int argc, mrb_value *argv, bool initialize)
{
  mrb_value object;
  RBasic *basic = mrb_obj_alloc(mrb, MRB_TT_DATA, clazz);
  object = mrb_obj_value(basic);
  if (initialize) mrb_funcall_argv(mrb, object, mrb_intern(mrb, "initialize"), argc, argv);
  return object;
}

mrb_value RubyEngine::newInstance(const char *classname, int argc, mrb_value *argv, bool callInit)
{
  return newInstance(getClass(classname), argc, argv, callInit);
}
