#include "BaseFont.hpp"

using namespace RubyAction;

BaseFont::BaseFont(mrb_value self)
  : RubyObject(self)
{
}

static mrb_value BaseFont_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_raise(mrb, E_RUNTIME_ERROR, "The BaseFont can't be instantiated. Please use one of this subclasses.");
  return self;
}

void RubyAction::bindBaseFont(mrb_state *mrb, RClass *module)
{
  struct RClass *clazz = mrb_define_class_under(mrb, module, "BaseFont", mrb->object_class);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", BaseFont_initialize, MRB_ARGS_NONE());
}
