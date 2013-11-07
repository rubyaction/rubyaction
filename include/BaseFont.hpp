#ifndef __BASE_FONT__
#define __BASE_FONT__

#include "RubyObject.hpp"
#include <mruby.h>
#include <SDL.h>

namespace RubyAction
{

  class BaseFont : public RubyObject
  {
  public:
    BaseFont(mrb_value);
    virtual void render(SDL_Renderer *, const SDL_Rect *, const char *, SDL_Color) = 0;
  };

  void bindBaseFont(mrb_state*, RClass*);

}

#endif // __BASE_FONT__
