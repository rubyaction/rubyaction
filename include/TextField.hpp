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
  protected:
    virtual void renderMe(sf::RenderTarget *);
  public:
    TextField(mrb_value, mrb_value, const char *);
    void setText(const char *);
    const char * getText();
  };

  void bindTextField(mrb_state*, RClass*);

}

#endif // __TEXT_FIELD__
