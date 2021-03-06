#include "TextureBase.hpp"

using namespace RubyAction;

TextureBase::TextureBase(mrb_value self)
  : RubyObject(self),
    width(0),
    height(0)
{
}

int TextureBase::getWidth()
{
  return width;
}

int TextureBase::getHeight()
{
  return height;
}

static mrb_value TextureBase_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_raise(mrb, E_RUNTIME_ERROR, "The TextureBase can't be instantiated. Please use one of subclasses.");
  return self;
}

static mrb_value TextureBase_getWidth(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(unwrap<TextureBase>(self)->getWidth());
}

static mrb_value TextureBase_getHeight(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(unwrap<TextureBase>(self)->getHeight());
}

void RubyAction::bindTextureBase(mrb_state *mrb, RClass *module)
{
  struct RClass *clazz = mrb_define_class_under(mrb, module, "TextureBase", mrb->object_class);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", TextureBase_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "width", TextureBase_getWidth, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "height", TextureBase_getHeight, MRB_ARGS_NONE());
}
