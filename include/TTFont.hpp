#ifndef __TTFONT__
#define __TTFONT__

#include "BaseFont.hpp"
#include "SDL_ttf.h"
#include <map>

namespace RubyAction
{

  class TTFont : public BaseFont
  {
  private:
    struct Glyph {
      int w, h, minx, maxy, advance;
      SDL_Texture *texture;
    };

    typedef std::map<char, Glyph*> GlyphCache;

    GlyphCache glyphs;
    TTF_Font *font;
    Glyph * getGlyph(SDL_Renderer *, char);
  public:
    TTFont(mrb_value, const char *, int);
    ~TTFont();
    virtual void render(SDL_Renderer *, const SDL_Rect *, const char *, SDL_Color);
  };

  void bindTTFont(mrb_state*, RClass*);

}

#endif // __TTFONT__
