#include "Font.hpp"

using namespace RubyAction;

Font::Font(mrb_value self, const char *texture, const char *descriptor)
  : BaseFont(self)
{
}

static mrb_value Font_initialize(mrb_state *mrb, mrb_value self)
{
  return self;
}

void RubyAction::bindFont(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "BaseFont");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "Font", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", Font_initialize, MRB_ARGS_NONE());
}
