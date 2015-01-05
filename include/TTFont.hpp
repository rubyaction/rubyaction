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
    void render(sf::RenderTarget&, const sf::Transform&, const sf::IntRect&, const sf::Color&, const char *);
  };

  void bindTTFont(mrb_state*, RClass*);

}

#endif // __TTFONT__
