#include "TextField.hpp"
#include "FontBase.hpp"
#include "util/array.hpp"

using namespace RubyAction;

TextField::TextField(mrb_value self, mrb_value font, const char *text)
  : Sprite(self),
    text(text)
{
  setProperty("font", font);
}

void TextField::renderMe(sf::RenderTarget *renderer)
{
  sf::Transform transform = this->getTransform();
  sf::Color color = this->getColor();
  const sf::IntRect bounds(0, 0, getWidth(), getHeight());
  FontBase *font = (FontBase*) getObject("font");
  font->render(*renderer, transform, bounds, color, text.c_str());
}

void TextField::setText(const char *text)
{
  this->text = std::string(text);
}

const char * TextField::getText()
{
  return text.c_str();
}

static mrb_value TextField_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value font;
  const char *text;
  size_t length;
  mrb_get_args(mrb, "os", &font, &text, &length);

  RubyEngine *engine = RubyEngine::getInstance();

  if (!mrb_obj_is_kind_of(mrb, font, engine->getClass("FontBase")))
    mrb_raise(mrb, E_TYPE_ERROR, "expected FontBase");

  wrap(self, new TextField(self, font, text));
  return self;
}

static mrb_value TextField_setText(mrb_state *mrb, mrb_value self)
{
  const char *text;
  size_t length;
  mrb_get_args(mrb, "s", &text, &length);
  unwrap<TextField>(self)->setText(text);
  return self;
}

static mrb_value TextField_getText(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, unwrap<TextField>(self)->getText());
}

void RubyAction::bindTextField(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "Sprite");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "TextField", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", TextField_initialize, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, clazz, "text=", TextField_setText, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "text", TextField_getText, MRB_ARGS_NONE());
}
