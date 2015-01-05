#ifndef __TEXTURE_BASE__
#define __TEXTURE_BASE__

#include "RubyObject.hpp"
#include <SFML/Graphics.hpp>
#include <mruby.h>

namespace RubyAction
{

  class TextureBase : public RubyObject
  {
  protected:
    int width;
    int height;
  public:
    TextureBase(mrb_value);
    int getWidth();
    int getHeight();
    virtual void render(sf::RenderTarget&, const sf::Transform&, const sf::IntRect&, const sf::Color&) = 0;
  };

  void bindTextureBase(mrb_state*, RClass*);

}

#endif // __TEXTURE_BASE__
