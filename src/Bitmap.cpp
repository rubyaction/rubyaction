#include "Bitmap.hpp"
#include "TextureRegion.hpp"
#include <mruby/variable.h>

namespace RubyAction
{

  Bitmap::Bitmap(mrb_value self)
    : Sprite(self)
  {
  }

  void Bitmap::render(SDL_Renderer *renderer)
  {
  }

  static mrb_value Bitmap_initialize(mrb_state *mrb, mrb_value self)
  {
    mrb_value arg;
    mrb_get_args(mrb, "o", &arg);

    RubyEngine *engine = RubyEngine::getInstance();
    mrb_value textureRegion;

    if (mrb_obj_is_kind_of(mrb, arg, engine->getClass("Texture")))
      textureRegion = engine->newInstance("TextureRegion", 1, &arg);
    else if (mrb_obj_is_kind_of(mrb, arg, engine->getClass("TextureRegion")))
      textureRegion = arg;
    else
      mrb_raise(mrb, E_TYPE_ERROR, "expected Texture or TextureRegion");

    mrb_iv_set(mrb, self, mrb_intern(mrb, "texture_region"), textureRegion);

    GET_INSTANCE(textureRegion, region, TextureRegion)

    Bitmap *bitmap = new Bitmap(self);
    bitmap->setWidth(region->getWidth());
    bitmap->setHeight(region->getHeight());

    SET_INSTANCE(self, bitmap);
    return self;
  }

  void bindBitmap(mrb_state *mrb, RClass *module)
  {
    struct RClass *super = mrb_class_get_under(mrb, module, "Sprite");
    struct RClass *clazz = mrb_define_class_under(mrb, module, "Bitmap", super);
    MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

    mrb_define_method(mrb, clazz, "initialize", Bitmap_initialize, MRB_ARGS_REQ(1));
  }

}
