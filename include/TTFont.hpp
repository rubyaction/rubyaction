#ifndef __TTFONT__
#define __TTFONT__

#include "FontBase.hpp"

namespace RubyAction
{

  class TTFont : public FontBase
  {
  private:
    sf::Font font;
    sf::Text text;
  public:
    TTFont(mrb_value, const char *, int);
    virtual void render(sf::RenderTarget *, sf::Transform *, sf::Color *, sf::FloatRect, const char *);
  };

  void bindTTFont(mrb_state*, RClass*);

}

#endif // __TTFONT__
