#ifndef __TEXTURE__
#define __TEXTURE__

#include "TextureBase.hpp"

namespace RubyAction
{

  class Texture : public TextureBase
  {
  private:
    sf::Texture texture;
    sf::Sprite sprite;
  public:
    Texture(mrb_value self, const char *filename);
    virtual void render(sf::RenderTarget&, const sf::Transform&, const sf::IntRect&, const sf::Color&);
  };

  void bindTexture(mrb_state*, RClass*);

}

#endif // __TEXTURE__
