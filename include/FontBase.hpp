#ifndef __FONT_BASE__
#define __FONT_BASE__

#include "RubyObject.hpp"
#include <mruby.h>
#include <SFML/Graphics.hpp>

namespace RubyAction
{

  class FontBase : public RubyObject
  {
  public:
    FontBase(mrb_value);
    virtual void render(sf::RenderTarget *, sf::Transform *, sf::Color *, sf::FloatRect, const char *) = 0;
  };

  void bindFontBase(mrb_state*, RClass*);

}

#endif // __FONT_BASE__
