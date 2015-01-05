#include "TextureRegion.hpp"
#include "RubyEngine.hpp"
#include "util/array.hpp"
#include <mruby/variable.h>
#include <mruby/array.h>

using namespace RubyAction;

TextureRegion::TextureRegion(mrb_value self, int x, int y, int width, int height)
  : RubyObject(self)
{
  setRegion(x, y, width, height);
}

int TextureRegion::getX()
{
  return x;
}

int TextureRegion::getY()
{
  return y;
}

int TextureRegion::getWidth()
{
  return width;
}

int TextureRegion::getHeight()
{
  return height;
}

void TextureRegion::setRegion(int x, int y, int width, int height)
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

TextureBase* TextureRegion::getTextureBase()
{
  return (TextureBase*) getObject("texture_base");
}

static mrb_value TextureRegion_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value tex;
  mrb_int x;
  mrb_int y;
  mrb_int width;
  mrb_int height;
  int argc = mrb_get_args(mrb, "o|iiii", &tex, &x, &y, &width, &height);

  RClass *clazz = RubyEngine::getInstance()->getClass("TextureBase");
  if (!mrb_obj_is_kind_of(mrb, tex, clazz)) mrb_raise(mrb, E_TYPE_ERROR, "expected TextureBase");

  mrb_iv_set(mrb, self, mrb_intern(mrb, "texture_base"), tex);

  GET_INSTANCE(tex, texture, TextureBase)

  if (argc < 2) x = 0;
  if (argc < 3) y = 0;
  if (argc < 4) width = texture->getWidth() - x;
  if (argc < 5) height = texture->getHeight() - y;

  SET_INSTANCE(self, new TextureRegion(self, x, y, width, height))
  return self;
}

static mrb_value TextureRegion_getRegion(mrb_state *mrb, mrb_value self)
{
  GET_INSTANCE(self, textureRegion, TextureRegion)
  mrb_value region[4] = {
    mrb_fixnum_value(textureRegion->getX()),
    mrb_fixnum_value(textureRegion->getY()),
    mrb_fixnum_value(textureRegion->getWidth()),
    mrb_fixnum_value(textureRegion->getHeight())
  };
  return mrb_ary_new_from_values(mrb, 4, region);
}

static mrb_value TextureRegion_setRegion(mrb_state *mrb, mrb_value self)
{
  mrb_value region;
  mrb_get_args(mrb, "A", &region);

  GET_INSTANCE(self, textureRegion, TextureRegion)
  textureRegion->setRegion(
    A_GET_INT(region, 0),
    A_GET_INT(region, 1),
    A_GET_INT(region, 2),
    A_GET_INT(region, 3)
  );
  return self;
}

void RubyAction::bindTextureRegion(mrb_state *mrb, RClass *module)
{
  struct RClass *clazz = mrb_define_class_under(mrb, module, "TextureRegion", mrb->object_class);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", TextureRegion_initialize, MRB_ARGS_ARG(1, 4));
  mrb_define_method(mrb, clazz, "region", TextureRegion_getRegion, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "region=", TextureRegion_setRegion, MRB_ARGS_REQ(1));
}
