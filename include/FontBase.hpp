#ifndef __FONT_BASE__
#define __FONT_BASE__

#include "RubyObject.hpp"
#include <SFML/Graphics.hpp>

namespace RubyAction
{

  class FontBase : public RubyObject
  {
  public:
    FontBase(mrb_value);
    virtual void render(sf::RenderTarget&, const sf::Transform&, const sf::IntRect&, const sf::Color&, const char *) = 0;
  };

  void bindFontBase(mrb_state*, RClass*);

}

#endif // __FONT_BASE__
