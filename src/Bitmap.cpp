#include "Bitmap.hpp"
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

    struct RClass *module = mrb_class_get(mrb, "RubyAction");
    struct RClass *texture = mrb_class_get_under(mrb, module, "Texture");
    struct RClass *textureRegion = mrb_class_get_under(mrb, module, "Sprite");

    if (mrb_obj_is_kind_of(mrb, arg, texture))
    {
      mrb_iv_set(mrb, self, mrb_intern(mrb, "texture"), arg);
    }
    else if (mrb_obj_is_kind_of(mrb, arg, textureRegion))
    {
      mrb_iv_set(mrb, self, mrb_intern(mrb, "region"), arg);
    }
    else
    {
      mrb_raise(mrb, E_TYPE_ERROR, "expected Texture or TextureRegion");
    }

    SET_INSTANCE(new Bitmap(self));
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
