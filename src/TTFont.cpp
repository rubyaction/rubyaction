#include "TTFont.hpp"
#include <sstream>

using namespace RubyAction;

TTFont::TTFont(mrb_value self, const char *filename, int size)
  : BaseFont(self)
{
  if (!TTF_WasInit() && TTF_Init() < 0) mrb_raise(mrb, E_RUNTIME_ERROR, TTF_GetError());

  font = TTF_OpenFont(filename, size);
  if (!font) {
    std::stringstream message;
    message << filename << " not found!";
    mrb_raise(mrb, E_ARGUMENT_ERROR, message.str().c_str());
  }
}

TTFont::~TTFont()
{
  TTF_CloseFont(font);
}

void TTFont::render(SDL_Renderer *renderer, const SDL_Rect *srcrect, const char *text, SDL_Color color)
{
  SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_RenderCopy(renderer, texture, NULL, srcrect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

static mrb_value TTFont_initialize(mrb_state *mrb, mrb_value self)
{
  const char *filename;
  size_t length;
  mrb_int size;
  mrb_get_args(mrb, "si", &filename, &length, &size);

  SET_INSTANCE(self, new TTFont(self, filename, size));
  return self;
}

void RubyAction::bindTTFont(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "BaseFont");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "TTFont", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", TTFont_initialize, MRB_ARGS_NONE());
}
