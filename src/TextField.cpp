#include "TextField.hpp"
#include "BaseFont.hpp"

using namespace RubyAction;

TextField::TextField(mrb_value self, mrb_value font, const char *text)
  : Sprite(self),
    text(text)
{
  setProperty("font", font);
}

void TextField::renderMe(SDL_Renderer *renderer)
{
  BaseFont *font = (BaseFont*) this->getObject("font");
  SDL_Color color = { 255, 255, 255 };
  SDL_Rect dstrect = { 0, 0, this->getWidth(), this->getHeight() };
  font->render(renderer, &dstrect, text, color);
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

void RubyAction::bindTextField(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "Sprite");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "TextField", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", TextField_initialize, MRB_ARGS_REQ(2));
}
