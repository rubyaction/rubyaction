#ifndef __FONT_BASE__
#define __FONT_BASE__

#include "RubyObject.hpp"
#include <mruby.h>
#include <SDL.h>

namespace RubyAction
{

  class FontBase : public RubyObject
  {
  public:
    FontBase(mrb_value);
    virtual void render(SDL_Renderer *, const SDL_Rect *, const char *, SDL_Color) = 0;
  };

  void bindFontBase(mrb_state*, RClass*);

}

#endif // __FONT_BASE__
