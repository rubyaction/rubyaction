#include "TTFont.hpp"
#include <sstream>
#include <cstring>

using namespace RubyAction;

TTFont::TTFont(mrb_value self, const char *filename, int size) : FontBase(self)
{
  if (!font.loadFromFile(filename))
  {
    std::stringstream message;
    message << "TrueType font not found: " << filename;
    mrb_raise(mrb, E_ARGUMENT_ERROR, message.str().c_str());
  }
  text.setFont(font);
  text.setCharacterSize(size);
}

void TTFont::render(sf::RenderTarget *renderer, sf::Transform *transform, sf::Color *color,
  sf::FloatRect bounds, const char *text)
{
  this->text.setString(text);
  this->text.setColor(*color);

  sf::FloatRect localBounds = this->text.getLocalBounds();
  sf::Transform localTransform;
  localTransform.scale(bounds.width / localBounds.width, bounds.height / localBounds.height);
  localTransform.translate(-localBounds.left, -localBounds.top);

  renderer->draw(this->text, (*transform) * localTransform);
}

static mrb_value TTFont_initialize(mrb_state *mrb, mrb_value self)
{
  const char *filename;
  size_t length;
  mrb_int size;
  mrb_get_args(mrb, "si", &filename, &length, &size);

  SET_INSTANCE(self, new TTFont(self, filename, size));
  return self;
}

void RubyAction::bindTTFont(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "FontBase");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "TTFont", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", TTFont_initialize, MRB_ARGS_REQ(2));
}
