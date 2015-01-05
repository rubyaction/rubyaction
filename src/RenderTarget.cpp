#include "RenderTarget.hpp"

using namespace RubyAction;

RenderTarget::RenderTarget(mrb_value self, float width, float height)
  : TextureBase(self)
{
  this->width = width;
  this->height = height;
  texture.create(width, height);
  texture.clear(sf::Color::Transparent);
}

void RenderTarget::draw(Sprite* sprite)
{
  sprite->render(&texture);
  texture.display();
}

void RenderTarget::clear()
{
  texture.clear(sf::Color::Transparent);
  texture.display();
}

void RenderTarget::render(sf::RenderTarget &target, const sf::Transform &transform, const sf::IntRect &rect,
  const sf::Color &color)
{
  sprite.setTexture(texture.getTexture());
  sprite.setColor(color);
  sprite.setTextureRect(rect);
  target.draw(sprite, transform);
}

static mrb_value RenderTarget_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float width, height;
  mrb_get_args(mrb, "ff", &width, &height);

  SET_INSTANCE(self, new RenderTarget(self, width, height))
  return self;
}

static mrb_value RenderTarget_draw(mrb_state *mrb, mrb_value self)
{
  mrb_value s;
  mrb_get_args(mrb, "o", &s);

  struct RClass *module = mrb_class_get(mrb, "RubyAction");
  struct RClass *clazz = mrb_class_get_under(mrb, module, "Sprite");
  if (!mrb_obj_is_kind_of(mrb, s, clazz))
  {
    mrb_raise(mrb, E_TYPE_ERROR, "expected Sprite");
  }

  GET_INSTANCE(self, renderTarget, RenderTarget)
  GET_INSTANCE(s, sprite, Sprite)
  renderTarget->draw(sprite);
  return self;
}

static mrb_value RenderTarget_clear(mrb_state *mrb, mrb_value self)
{
  GET_INSTANCE(self, renderTarget, RenderTarget)
  renderTarget->clear();
  return self;
}

void RubyAction::bindRenderTarget(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "TextureBase");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "RenderTarget", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", RenderTarget_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "draw", RenderTarget_draw, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "clear", RenderTarget_clear, MRB_ARGS_NONE());
}
