#ifndef __TEXT_FIELD__
#define __TEXT_FIELD__

#include "Sprite.hpp"

namespace RubyAction
{

  class TextField : public Sprite
  {
  private:
    const char *text;
    SDL_Color color;
  protected:
    virtual void renderMe(SDL_Renderer *);
  public:
    TextField(mrb_value, mrb_value, const char *);
    void setColor(SDL_Color);
    SDL_Color getColor();
  };

  void bindTextField(mrb_state*, RClass*);

}

#endif // __TEXT_FIELD__
