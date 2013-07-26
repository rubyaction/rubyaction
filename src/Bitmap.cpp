#include "Bitmap.hpp"
#include "TextureRegion.hpp"
#include <mruby/variable.h>

namespace RubyAction
{

  Bitmap::Bitmap(mrb_value self, mrb_value texture_region)
    : Sprite(self)
  {
    setProperty("texture_region", texture_region);
    TextureRegion *region = (TextureRegion*) getObject("texture_region");
    setWidth(region->getWidth());
    setHeight(region->getHeight());
  }

  void Bitmap::render(SDL_Renderer *renderer)
  {
    if (!isVisible()) return;

    TextureRegion *region = (TextureRegion*) this->getObject("texture_region");
    Texture *texture = (Texture*) region->getObject("texture");

    SDL_Rect srcrect = { region->getX(), region->getY(), region->getWidth(), region->getHeight() };
    SDL_Rect dstrect = {
      this->getX(),
      this->getY(),
      static_cast<int>(this->getWidth() * this->getScaleX()),
      static_cast<int>(this->getHeight() * this->getScaleY())
    };

    texture->render(renderer, &srcrect, &dstrect, getRotation(), NULL, SDL_FLIP_NONE);
    Sprite::render(renderer);
  }

  static mrb_value Bitmap_initialize(mrb_state *mrb, mrb_value self)
  {
    mrb_value arg;
    mrb_get_args(mrb, "o", &arg);

    RubyEngine *engine = RubyEngine::getInstance();
    mrb_value texture_region;

    if (mrb_obj_is_kind_of(mrb, arg, engine->getClass("TextureBase")))
      texture_region = engine->newInstance("TextureRegion", 1, &arg);
    else if (mrb_obj_is_kind_of(mrb, arg, engine->getClass("TextureRegion")))
      texture_region = arg;
    else
      mrb_raise(mrb, E_TYPE_ERROR, "expected TextureBase or TextureRegion");

    SET_INSTANCE(self, new Bitmap(self, texture_region));
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
