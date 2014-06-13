#include "TTFont.hpp"
#include <sstream>
#include <cstring>

using namespace RubyAction;

TTFont::TTFont(mrb_value self, const char *filename, int size) : FontBase(self)
{
  if (!(font = TTF_OpenFont(filename, size)))
  {
    std::stringstream message;
    message << "TrueType font not found: " << filename;
    mrb_raise(mrb, E_ARGUMENT_ERROR, message.str().c_str());
  }
}

TTFont::~TTFont()
{
  TTF_CloseFont(font);
  std::map<char, Glyph*>::iterator iterator;
  for (iterator = glyphs.begin(); iterator != glyphs.end(); iterator++)
  {
    SDL_DestroyTexture(iterator->second->texture);
    delete iterator->second;
  }
}

void TTFont::render(SDL_Renderer *renderer, const SDL_Rect *dstrect, const char *text, SDL_Color color)
{
  int x = dstrect->x;
  int y = dstrect->y;
  int width, height;
  TTF_SizeUTF8(font, text, &width, &height);
  float wr = dstrect->w / (float) width;
  float hr = dstrect->h / (float) height;

  for (int i = 0; i < strlen(text); i++)
  {
    char ch = text[i];
    Glyph *glyph = this->getGlyph(renderer, ch);

    int w = glyph->w * wr;
    int h = glyph->h * hr;
    SDL_Rect rect = { x, y, w, h };

    SDL_SetTextureColorMod(glyph->texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(glyph->texture, color.a);
    SDL_RenderCopy(renderer, glyph->texture, NULL, &rect);

    x += glyph->advance * wr;
  }
}

TTFont::Glyph * TTFont::getGlyph(SDL_Renderer *renderer, char ch)
{
  Glyph *glyph;
  if (!(glyph = glyphs[ch]))
  {
    SDL_Surface *surface = TTF_RenderGlyph_Blended(font, ch, {255, 255, 255, 255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    glyph = new Glyph();
    glyph->w = surface->w;
    glyph->h = surface->h;
    glyph->texture = texture;

    TTF_GlyphMetrics(font, ch, NULL, NULL, NULL, NULL, &(glyph->advance));

    glyphs[ch] = glyph;
    SDL_FreeSurface(surface);
  }
  return glyph;
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
  struct RClass *super = mrb_class_get_under(mrb, module, "FontBase");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "TTFont", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", TTFont_initialize, MRB_ARGS_REQ(2));
}
