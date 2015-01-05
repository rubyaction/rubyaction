#ifndef __TEXT_FIELD__
#define __TEXT_FIELD__

#include "Sprite.hpp"
#include <string>
#include <SFML/Graphics.hpp>

namespace RubyAction
{

  class TextField : public Sprite
  {
  private:
    std::string text;
    sf::Color *color;
  protected:
    virtual void renderMe(sf::RenderTarget *, sf::Transform *);
  public:
    TextField(mrb_value, mrb_value, const char *);
    ~TextField();
    void setColor(sf::Color*);
    sf::Color * getColor();
    void setText(const char *);
    const char * getText();
  };

  void bindTextField(mrb_state*, RClass*);

}

#endif // __TEXT_FIELD__
