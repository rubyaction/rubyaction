#include "TextField.hpp"
#include "BaseFont.hpp"
#include "util/array.hpp"

using namespace RubyAction;

TextField::TextField(mrb_value self, mrb_value font, const char *text)
  : Sprite(self),
    text(text),
    color({255, 255, 255, 255})
{
  setProperty("font", font);
}

void TextField::renderMe(SDL_Renderer *renderer)
{
  BaseFont *font = (BaseFont*) this->getObject("font");
  SDL_Rect dstrect = { 0, 0, this->getWidth(), this->getHeight() };
  font->render(renderer, &dstrect, text, color);
}

void TextField::setColor(SDL_Color color)
{
  this->color = color;
}

SDL_Color TextField::getColor()
{
  return color;
}

static mrb_value TextField_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value font;
  const char *text;
  size_t length;
  mrb_get_args(mrb, "os", &font, &text, &length);

  RubyEngine *engine = RubyEngine::getInstance();

  if (!mrb_obj_is_kind_of(mrb, font, engine->getClass("BaseFont")))
    mrb_raise(mrb, E_TYPE_ERROR, "expected BaseFont");

  SET_INSTANCE(self, new TextField(self, font, text));
  return self;
}

static mrb_value TextField_setColor(mrb_state *mrb, mrb_value self)
{
  mrb_value c;
  mrb_get_args(mrb, "A", &c);

  SDL_Color color = {
    (Uint8) A_GET_INT(c, 0),
    (Uint8) A_GET_INT(c, 1),
    (Uint8) A_GET_INT(c, 2),
    (A_SIZE(c) == 3) ? (Uint8) 255 : (Uint8) A_GET_INT(c, 3)
  };

  GET_INSTANCE(self, textField, TextField)
  textField->setColor(color);
  return self;
}

static mrb_value TextField_getColor(mrb_state *mrb, mrb_value self)
{
  GET_INSTANCE(self, textField, TextField)
  SDL_Color c = textField->getColor();

  mrb_value color[4] = {
    mrb_fixnum_value(c.r),
    mrb_fixnum_value(c.g),
    mrb_fixnum_value(c.b),
    mrb_fixnum_value(c.a)
  };
  return mrb_ary_new_from_values(mrb, 4, color);
}


void RubyAction::bindTextField(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "Sprite");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "TextField", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", TextField_initialize, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, clazz, "color=", TextField_setColor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "color", TextField_getColor, MRB_ARGS_NONE());
}
