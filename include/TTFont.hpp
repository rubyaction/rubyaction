#ifndef __TTFONT__
#define __TTFONT__

#include "BaseFont.hpp"
#include "SDL_ttf.h"

namespace RubyAction
{

  class TTFont : public BaseFont
  {
  private:
    TTF_Font *font;
  public:
    TTFont(mrb_value, const char *, int);
    ~TTFont();
    virtual void render(SDL_Renderer *, const SDL_Rect *, const char *, SDL_Color);
  };

  void bindTTFont(mrb_state*, RClass*);

}

#endif // __TTFONT__
