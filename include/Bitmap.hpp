#ifndef __BITMAP__
#define __BITMAP__

#include "Sprite.hpp"

namespace RubyAction
{

  class Bitmap : public Sprite
  {
  public:
  	Bitmap(mrb_value, mrb_value);
  	virtual void render(SDL_Renderer *);
  };

  void bindBitmap(mrb_state*, RClass*);

}

#endif // __BITMAP__
