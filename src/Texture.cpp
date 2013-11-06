#include "Texture.hpp"
#include "Application.hpp"
#include <SDL_image.h>

namespace RubyAction
{

  Texture::Texture(mrb_value self, const char *filename) : TextureBase(self)
  {
    surface = IMG_Load(filename);

    this->width = surface->w;
    this->height = surface->h;
    this->texture = NULL;
  }

  Texture::~Texture()
  {
    SDL_DestroyTexture(texture);
  }

  void Texture::load(SDL_Renderer *renderer)
  {
    if (!texture)
    {
      texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_FreeSurface(surface);
    }
  }

  void Texture::render(SDL_Renderer *renderer, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
  {
    load(renderer);
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
  }

  static mrb_value Texture_initialize(mrb_state *mrb, mrb_value self)
  {
    const char *filename;
    size_t length;
    mrb_get_args(mrb, "s", &filename, &length);

    SET_INSTANCE(self, new Texture(self, filename))
    return self;
  }

  void bindTexture(mrb_state *mrb, RClass *module)
  {
    struct RClass *super = mrb_class_get_under(mrb, module, "TextureBase");
    struct RClass *clazz = mrb_define_class_under(mrb, module, "Texture", super);
    MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

    mrb_define_method(mrb, clazz, "initialize", Texture_initialize, MRB_ARGS_REQ(1));
  }

}
