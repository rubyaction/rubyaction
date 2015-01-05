#include "Bitmap.hpp"
#include "TextureRegion.hpp"
#include <mruby/variable.h>

using namespace RubyAction;

Bitmap::Bitmap(mrb_value self, mrb_value texture_region)
  : Sprite(self)
{
  setProperty("texture_region", texture_region);
  TextureRegion *region = (TextureRegion*) getObject("texture_region");
  setWidth(region->getWidth());
  setHeight(region->getHeight());
}

void Bitmap::renderMe(sf::RenderTarget *renderer)
{
  sf::Transform transform = this->getTransform();
  TextureRegion *region = (TextureRegion*) this->getObject("texture_region");
  TextureBase *texture = region->getTextureBase();
  sf::IntRect rect(region->getX(), region->getY(), region->getWidth(), region->getHeight());
  sf::Color color = this->getColor();

  texture->render(*renderer, transform, rect, color);
}

static mrb_value Bitmap_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value arg;
  mrb_get_args(mrb, "o", &arg);

  RubyEngine *engine = RubyEngine::getInstance();
  mrb_value texture_region;

  if (mrb_obj_is_kind_of(mrb, arg, engine->getClass("TextureBase")))
    texture_region = engine->newInstance("TextureRegion", &arg, 1);
  else if (mrb_obj_is_kind_of(mrb, arg, engine->getClass("TextureRegion")))
    texture_region = arg;
  else
    mrb_raise(mrb, E_TYPE_ERROR, "expected TextureBase or TextureRegion");

  SET_INSTANCE(self, new Bitmap(self, texture_region));
  return self;
}

void RubyAction::bindBitmap(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "Sprite");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "Bitmap", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", Bitmap_initialize, MRB_ARGS_REQ(1));
}
