#ifndef __RENDER_TARGET__
#define __RENDER_TARGET__

#include "TextureBase.hpp"
#include "Sprite.hpp"

namespace RubyAction
{

  class RenderTarget : public TextureBase
  {
  private:
    sf::RenderTexture texture;
    sf::Sprite sprite;
  public:
    RenderTarget(mrb_value self, float, float);
    void draw(Sprite*);
    void clear();
    virtual void render(sf::RenderTarget&, const sf::Transform&, const sf::IntRect&, const sf::Color&);
  };

  void bindRenderTarget(mrb_state*, RClass*);

}

#endif // __RENDER_TARGET__
