#ifndef __TEXTURE__
#define __TEXTURE__

#include "TextureBase.hpp"
#include <SFML/Graphics.hpp>

namespace RubyAction
{

  class Texture : public TextureBase
  {
  private:
  	sf::Texture texture;
    sf::Sprite sprite;
  public:
    Texture(mrb_value self, const char *filename);
    void render(sf::RenderTarget &target, const sf::Transform &transform, const sf::IntRect &rect);
  };

  void bindTexture(mrb_state*, RClass*);

}

#endif // __TEXTURE__
