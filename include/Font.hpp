#ifndef __FONT__
#define __FONT__

#include "FontBase.hpp"
#include <map>

namespace RubyAction
{

  class Font : public FontBase
  {
  private:
    struct TextureGlyph {
      char chr;
      int x, y;
      int width, height;
      int left, top;
      int advancex;
    };

    struct
    {
      int size;
      bool smooth;
      int height;
      int ascender;
      std::map<char, TextureGlyph> glyphs;
    } fontInfo;

    sf::Texture texture;
    sf::Sprite sprite;

    sf::IntRect getTextBounds(const char *);

  public:
    Font(mrb_value, const char *, const char *);
    virtual void render(sf::RenderTarget&, const sf::Transform&, const sf::IntRect&, const sf::Color&, const char *);
  };

  void bindFont(mrb_state*, RClass*);

}

#endif // __FONT__
