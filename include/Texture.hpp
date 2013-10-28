#ifndef __TEXTURE__
#define __TEXTURE__

#include "TextureBase.hpp"
#include <SDL.h>

namespace RubyAction
{

  class Texture : public TextureBase
  {
  private:
  	SDL_Surface *surface;
    SDL_Texture *texture;
  public:
    Texture(mrb_value, const char *);
    ~Texture();
    void load(SDL_Renderer *);
    bool loaded();
    void unload();
    void render(SDL_Renderer *,
              const SDL_Rect *,
              const SDL_Rect *,
              const double,
              const SDL_Point *,
              const SDL_RendererFlip);
  };

  void bindTexture(mrb_state*, RClass*);

}

#endif // __TEXTURE__
