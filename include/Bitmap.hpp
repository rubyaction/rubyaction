#ifndef __BITMAP__
#define __BITMAP__

#include "Sprite.hpp"

namespace RubyAction
{

  class Bitmap : public Sprite
  {
  protected:
    virtual void renderMe(SDL_Renderer *);
  public:
    Bitmap(mrb_value, mrb_value);
  };

  void bindBitmap(mrb_state*, RClass*);

}

#endif // __BITMAP__
