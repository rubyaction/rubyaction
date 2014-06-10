#ifndef __TEXTURE__
#define __TEXTURE__

#include "TextureBase.hpp"
#include <SDL.h>

namespace RubyAction
{

  class Texture : public TextureBase
  {
  private:
  	SDL_Texture *texture;
    void load(SDL_Renderer *);
  public:
    Texture(mrb_value, const char *);
    ~Texture();
    void render(SDL_Renderer *, const SDL_Rect *, const SDL_Rect *);
  };

  void bindTexture(mrb_state*, RClass*);

}

#endif // __TEXTURE__
