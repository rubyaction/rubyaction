#include "Sprite.hpp"
#include "util/array.hpp"
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/variable.h>

using namespace RubyAction;

Sprite::Sprite(mrb_value self)
  : EventDispatcher(self),
    x(0),
    y(0),
    width(0),
    height(0),
    scaleX(1),
    scaleY(1),
    anchorX(0),
    anchorY(0),
    rotation(0),
    visible(true),
    color(sf::Color::White)
{
  if (!mrb_nil_p(self))
  {
    setProperty("children", mrb_ary_new(mrb));
  }
}

float Sprite::getX()
{
  return x;
}

void Sprite::setX(float x)
{
  this->x = x;
}

float Sprite::getY()
{
  return y;
}

void Sprite::setY(float y)
{
  this->y = y;
}

int Sprite::getWidth()
{
  return width;
}

void Sprite::setWidth(int width)
{
  this->width = width;
}

int Sprite::getHeight()
{
  return height;
}

void Sprite::setHeight(int height)
{
  this->height = height;
}

float Sprite::getScaleX()
{
  return scaleX;
}

void Sprite::setScaleX(float scaleX)
{
  this->scaleX = scaleX;
}

float Sprite::getScaleY()
{
  return scaleY;
}

void Sprite::setScaleY(float scaleY)
{
  this->scaleY = scaleY;
}

float Sprite::getAnchorX()
{
  return anchorX;
}

void Sprite::setAnchorX(float anchorX)
{
  this->anchorX = anchorX;
}

float Sprite::getAnchorY()
{
  return anchorY;
}

void Sprite::setAnchorY(float anchorY)
{
  this->anchorY = anchorY;
}

float Sprite::getRotation()
{
  return rotation;
}

void Sprite::setRotation(float rotation)
{
  this->rotation = rotation;
}

bool Sprite::isVisible()
{
  return visible;
}

void Sprite::setVisible(bool visible)
{
  this->visible = visible;
}

Sprite* Sprite::getParent()
{
  return mrb_nil_p(getProperty("parent")) ? NULL : (Sprite*) getObject("parent");
}

void Sprite::setParent(Sprite *parent)
{
  setProperty("parent", parent ? parent->getSelf() : mrb_nil_value());
}

void Sprite::setColor(sf::Color color)
{
  this->color = color;
}

const sf::Color& Sprite::getColor()
{
  return color;
}

void Sprite::render(sf::RenderTarget *renderer)
{
  if (!isVisible()) return;

  this->renderMe(renderer);

  mrb_value children = getProperty("children");
  for (int i = 0; i < RARRAY_LEN(children); i++)
  {
    mrb_value child = mrb_ary_ref(mrb, children, i);
    unwrap<Sprite>(child)->render(renderer);
  }
}

void Sprite::addChild(mrb_value child)
{
  if (!contains(child))
  {
    mrb_ary_push(mrb, getProperty("children"), child);
    Sprite* childSprite = unwrap<Sprite>(child);
    childSprite->removeFromParent();
    childSprite->setParent(this);
  }
}

void Sprite::removeChild(mrb_value child)
{
  if (contains(child))
  {
    mrb_value old = getProperty("children");
    mrb_value children = mrb_ary_new(mrb);

    for (int i = 0; i < RARRAY_LEN(old); i++)
    {
      mrb_value current = mrb_ary_ref(mrb, old, i);
      if (!mrb_obj_equal(mrb, child, current)) mrb_ary_push(mrb, children, current);
    }

    setProperty("children", children);
    unwrap<Sprite>(child)->setParent(NULL);
  }
}

void Sprite::removeFromParent()
{
  Sprite *parent = this->getParent();
  if (parent) parent->removeChild(this->getSelf());
}

bool Sprite::contains(mrb_value child)
{
  mrb_value children = getProperty("children");
  for (int i = 0; i < RARRAY_LEN(children); i++)
  {
    mrb_value current = mrb_ary_ref(mrb, children, i);
    if (mrb_obj_equal(mrb, child, current)) return true;
  }
  return false;
}

sf::FloatRect Sprite::getBounds(Sprite* other)
{
  sf::FloatRect bounds(0, 0, width, height);
  bounds = this->getTransform().transformRect(bounds);
  bounds = other->getTransform().getInverse().transformRect(bounds);
  return bounds;
}

void Sprite::globalToLocal(float gx, float gy, float* x, float* y)
{
  sf::Transform inverse = this->getTransform().getInverse();
  sf::Vector2f local = inverse.transformPoint(gx, gy);
  *x = local.x;
  *y = local.y;
}

void Sprite::localToGlobal(float x, float y, float* gx, float* gy)
{
  sf::Transform transform = this->getTransform();
  sf::Vector2f global = transform.transformPoint(x, y);
  *gx = global.x;
  *gy = global.y;
}

bool Sprite::collide(float gx, float gy)
{
  float x, y;
  this->globalToLocal(gx, gy, &x, &y);
  return (x >= 0) && (x <= width) && (y >= 0) && (y <= height);
}

void Sprite::dispatch(mrb_sym name, mrb_value* argv, int argc)
{
  mrb_value children = getProperty("children");

  for (int i = 0; i < RARRAY_LEN(children); i++)
  {
    mrb_value child = mrb_ary_ref(mrb, children, i);
    unwrap<Sprite>(child)->dispatch(name, argv, argc);
  }

  EventDispatcher::dispatch(name, argv, argc);
}

const sf::Transform& Sprite::getTransform()
{
  sf::Transform anchor;
  anchor.translate(-width * scaleX * anchorX, -height * scaleY * anchorY);
  sf::Transform rotate;
  rotate.rotate(rotation);
  sf::Transform translate;
  translate.translate(x, y);
  sf::Transform scale;
  scale.scale(scaleX, scaleY);
  this->transform = translate * (rotate * anchor) * scale;

  Sprite *parent = this->getParent();
  if (parent) transform = parent->getTransform() * transform;

  return transform;
}

static mrb_value Sprite_initialize(mrb_state *mrb, mrb_value self)
{
  wrap(self, new Sprite(self));
  return self;
}

static mrb_value Sprite_getX(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, unwrap<Sprite>(self)->getX());
}

static mrb_value Sprite_setX(mrb_state *mrb, mrb_value self)
{
  mrb_float x;
  mrb_get_args(mrb, "f", &x);
  unwrap<Sprite>(self)->setX(x);
  return self;
}

static mrb_value Sprite_getY(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, unwrap<Sprite>(self)->getY());
}

static mrb_value Sprite_setY(mrb_state *mrb, mrb_value self)
{
  mrb_float y;
  mrb_get_args(mrb, "f", &y);
  unwrap<Sprite>(self)->setY(y);
  return self;
}

static mrb_value Sprite_getPosition(mrb_state *mrb, mrb_value self)
{
  mrb_value position[2] = { Sprite_getX(mrb, self), Sprite_getY(mrb, self) };
  return mrb_ary_new_from_values(mrb, 2, position);
}

static mrb_value Sprite_setPosition(mrb_state *mrb, mrb_value self)
{
  mrb_value position;
  mrb_get_args(mrb, "A", &position);
  Sprite* sprite = unwrap<Sprite>(self);
  sprite->setX(A_GET_FLOAT(position, 0));
  sprite->setY(A_GET_FLOAT(position, 1));
  return self;
}

static mrb_value Sprite_getWidth(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(unwrap<Sprite>(self)->getWidth());
}

static mrb_value Sprite_setWidth(mrb_state *mrb, mrb_value self)
{
  mrb_int width;
  mrb_get_args(mrb, "i", &width);
  unwrap<Sprite>(self)->setWidth(width);
  return self;
}

static mrb_value Sprite_getHeight(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(unwrap<Sprite>(self)->getHeight());
}

static mrb_value Sprite_setHeight(mrb_state *mrb, mrb_value self)
{
  mrb_int height;
  mrb_get_args(mrb, "i", &height);
  unwrap<Sprite>(self)->setHeight(height);
  return self;
}

static mrb_value Sprite_getSize(mrb_state *mrb, mrb_value self)
{
  mrb_value size[2] = { Sprite_getWidth(mrb, self), Sprite_getHeight(mrb, self) };
  return mrb_ary_new_from_values(mrb, 2, size);
}

static mrb_value Sprite_setSize(mrb_state *mrb, mrb_value self)
{
  mrb_value size;
  mrb_get_args(mrb, "A", &size);
  Sprite* sprite = unwrap<Sprite>(self);
  sprite->setWidth(A_GET_INT(size, 0));
  sprite->setHeight(A_GET_INT(size, 1));
  return self;
}

static mrb_value Sprite_getScaleX(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, unwrap<Sprite>(self)->getScaleX());
}

static mrb_value Sprite_setScaleX(mrb_state *mrb, mrb_value self)
{
  mrb_float scaleX;
  mrb_get_args(mrb, "f", &scaleX);
  unwrap<Sprite>(self)->setScaleX(scaleX);
  return self;
}

static mrb_value Sprite_getScaleY(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, unwrap<Sprite>(self)->getScaleY());
}

static mrb_value Sprite_setScaleY(mrb_state *mrb, mrb_value self)
{
  mrb_float scaleY;
  mrb_get_args(mrb, "f", &scaleY);
  unwrap<Sprite>(self)->setScaleY(scaleY);
  return self;
}

static mrb_value Sprite_getScale(mrb_state *mrb, mrb_value self)
{
  mrb_value scale[2] = { Sprite_getScaleX(mrb, self), Sprite_getScaleY(mrb, self) };
  return mrb_ary_new_from_values(mrb, 2, scale);
}

static mrb_value Sprite_setScale(mrb_state *mrb, mrb_value self)
{
  mrb_value scale;
  mrb_get_args(mrb, "A", &scale);
  Sprite* sprite = unwrap<Sprite>(self);
  sprite->setScaleX(A_GET_FLOAT(scale, 0));
  sprite->setScaleY(A_GET_FLOAT(scale, 1));
  return self;
}

static mrb_value Sprite_getAnchorX(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, unwrap<Sprite>(self)->getAnchorX());
}

static mrb_value Sprite_setAnchorX(mrb_state *mrb, mrb_value self)
{
  mrb_float anchorX;
  mrb_get_args(mrb, "f", &anchorX);
  unwrap<Sprite>(self)->setAnchorX(anchorX);
  return self;
}

static mrb_value Sprite_getAnchorY(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, unwrap<Sprite>(self)->getAnchorY());
}

static mrb_value Sprite_setAnchorY(mrb_state *mrb, mrb_value self)
{
  mrb_float anchorY;
  mrb_get_args(mrb, "f", &anchorY);
  unwrap<Sprite>(self)->setAnchorY(anchorY);
  return self;
}

static mrb_value Sprite_getAnchor(mrb_state *mrb, mrb_value self)
{
  mrb_value anchor[2] = { Sprite_getAnchorX(mrb, self), Sprite_getAnchorY(mrb, self) };
  return mrb_ary_new_from_values(mrb, 2, anchor);
}

static mrb_value Sprite_setAnchor(mrb_state *mrb, mrb_value self)
{
  mrb_value anchor;
  mrb_get_args(mrb, "A", &anchor);
  Sprite* sprite = unwrap<Sprite>(self);
  sprite->setAnchorX(A_GET_FLOAT(anchor, 0));
  sprite->setAnchorY(A_GET_FLOAT(anchor, 1));
  return self;
}

static mrb_value Sprite_getRotation(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, unwrap<Sprite>(self)->getRotation());
}

static mrb_value Sprite_setRotation(mrb_state *mrb, mrb_value self)
{
  mrb_float rotation;
  mrb_get_args(mrb, "f", &rotation);
  unwrap<Sprite>(self)->setRotation(rotation);
  return self;
}

static mrb_value Sprite_isVisible(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(unwrap<Sprite>(self)->isVisible());
}

static mrb_value Sprite_setVisible(mrb_state *mrb, mrb_value self)
{
  mrb_bool visible;
  mrb_get_args(mrb, "b", &visible);
  unwrap<Sprite>(self)->setVisible(visible);
  return self;
}

static mrb_value Sprite_getParent(mrb_state *mrb, mrb_value self)
{
  Sprite *parent = unwrap<Sprite>(self)->getParent();
  return parent ? parent->getSelf() : mrb_nil_value();
}

static mrb_value Sprite_getColor(mrb_state *mrb, mrb_value self)
{
  const sf::Color color = unwrap<Sprite>(self)->getColor();
  mrb_value c[4] = {
    mrb_float_value(mrb, float(color.r) / 255),
    mrb_float_value(mrb, float(color.g) / 255),
    mrb_float_value(mrb, float(color.b) / 255),
    mrb_float_value(mrb, float(color.a) / 255),
  };
  return mrb_ary_new_from_values(mrb, 4, c);
}

static mrb_value Sprite_setColor(mrb_state *mrb, mrb_value self)
{
  mrb_value color;
  mrb_get_args(mrb, "A", &color);

  unwrap<Sprite>(self)->setColor(
    sf::Color(
      A_GET_FLOAT(color, 0) * 255,
      A_GET_FLOAT(color, 1) * 255,
      A_GET_FLOAT(color, 2) * 255,
      A_GET_FLOAT(color, 3) * 255
    )
  );
  return self;
}

static mrb_value Sprite_addChild(mrb_state *mrb, mrb_value self)
{
  mrb_value child;
  mrb_get_args(mrb, "o", &child);

  struct RClass *module = mrb_class_get(mrb, "RubyAction");
  struct RClass *clazz = mrb_class_get_under(mrb, module, "Sprite");
  if (!mrb_obj_is_kind_of(mrb, child, clazz))
  {
    mrb_raise(mrb, E_TYPE_ERROR, "expected Sprite");
  }

  unwrap<Sprite>(self)->addChild(child);
  return self;
}

static mrb_value Sprite_removeChild(mrb_state *mrb, mrb_value self)
{
  mrb_value child;
  mrb_get_args(mrb, "o", &child);

  struct RClass *module = mrb_class_get(mrb, "RubyAction");
  struct RClass *clazz = mrb_class_get_under(mrb, module, "Sprite");
  if (!mrb_obj_is_kind_of(mrb, child, clazz))
  {
    mrb_raise(mrb, E_TYPE_ERROR, "expected Sprite");
  }

  unwrap<Sprite>(self)->removeChild(child);
  return self;
}

static mrb_value Sprite_removeFromParent(mrb_state *mrb, mrb_value self)
{
  unwrap<Sprite>(self)->removeFromParent();
  return self;
}

static mrb_value Sprite_contains(mrb_state *mrb, mrb_value self)
{
  mrb_value child;
  mrb_get_args(mrb, "o", &child);

  struct RClass *module = mrb_class_get(mrb, "RubyAction");
  struct RClass *clazz = mrb_class_get_under(mrb, module, "Sprite");
  if (!mrb_obj_is_kind_of(mrb, child, clazz))
  {
    mrb_raise(mrb, E_TYPE_ERROR, "expected Sprite");
  }

  return mrb_bool_value(unwrap<Sprite>(self)->contains(child));
}

static mrb_value Sprite_getBounds(mrb_state *mrb, mrb_value self)
{
  mrb_value other;
  mrb_get_args(mrb, "o", &other);

  struct RClass *module = mrb_class_get(mrb, "RubyAction");
  struct RClass *clazz = mrb_class_get_under(mrb, module, "Sprite");
  if (!mrb_obj_is_kind_of(mrb, other, clazz))
  {
    mrb_raise(mrb, E_TYPE_ERROR, "expected Sprite");
  }

  sf::FloatRect bounds = unwrap<Sprite>(self)->getBounds(unwrap<Sprite>(other));

  mrb_value point[4] = {
    mrb_float_value(mrb, bounds.left),
    mrb_float_value(mrb, bounds.top),
    mrb_float_value(mrb, bounds.width),
    mrb_float_value(mrb, bounds.height),
  };
  return mrb_ary_new_from_values(mrb, 4, point);
}

static mrb_value Sprite_globalToLocal(mrb_state *mrb, mrb_value self)
{
  mrb_float gx, gy;
  mrb_get_args(mrb, "ff", &gx, &gy);

  float x, y;
  unwrap<Sprite>(self)->globalToLocal(gx, gy, &x, &y);

  mrb_value point[2] = { mrb_float_value(mrb, x), mrb_float_value(mrb, y) };
  return mrb_ary_new_from_values(mrb, 2, point);
}

static mrb_value Sprite_localToGlobal(mrb_state *mrb, mrb_value self)
{
  mrb_float x, y;
  mrb_get_args(mrb, "ff", &x, &y);

  float gx, gy;
  unwrap<Sprite>(self)->localToGlobal(x, y, &gx, &gy);

  mrb_value point[2] = { mrb_float_value(mrb, gx), mrb_float_value(mrb, gy) };
  return mrb_ary_new_from_values(mrb, 2, point);
}

static mrb_value Sprite_collide(mrb_state *mrb, mrb_value self)
{
  mrb_float x, y;
  mrb_get_args(mrb, "ff", &x, &y);

  return mrb_bool_value(unwrap<Sprite>(self)->collide(x, y));
}

void RubyAction::bindSprite(mrb_state *mrb, RClass *module)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "EventDispatcher");
  struct RClass *clazz = mrb_define_class_under(mrb, module, "Sprite", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", Sprite_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "x", Sprite_getX, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "x=", Sprite_setX, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "y", Sprite_getY, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "y=", Sprite_setY, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "position", Sprite_getPosition, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "position=", Sprite_setPosition, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "width", Sprite_getWidth, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "width=", Sprite_setWidth, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "height", Sprite_getHeight, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "height=", Sprite_setHeight, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "size", Sprite_getSize, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "size=", Sprite_setSize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "scalex", Sprite_getScaleX, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "scalex=", Sprite_setScaleX, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "scaley", Sprite_getScaleY, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "scaley=", Sprite_setScaleY, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "scale", Sprite_getScale, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "scale=", Sprite_setScale, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "anchorx", Sprite_getAnchorX, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "anchorx=", Sprite_setAnchorX, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "anchory", Sprite_getAnchorY, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "anchory=", Sprite_setAnchorY, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "anchor", Sprite_getAnchor, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "anchor=", Sprite_setAnchor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "rotation", Sprite_getRotation, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "rotation=", Sprite_setRotation, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "visible?", Sprite_isVisible, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "visible=", Sprite_setVisible, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "parent", Sprite_getParent, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "color", Sprite_getColor, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "color=", Sprite_setColor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "add", Sprite_addChild, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "remove", Sprite_removeChild, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "remove_from_parent", Sprite_removeFromParent, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "contains?", Sprite_contains, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "bounds", Sprite_getBounds, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "to_local", Sprite_globalToLocal, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, clazz, "to_global", Sprite_localToGlobal, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, clazz, "collide?", Sprite_collide, MRB_ARGS_REQ(2));

  // alias
  mrb_alias_method(mrb, clazz, mrb_intern(mrb, "<<"), mrb_intern(mrb, "add"));
  mrb_alias_method(mrb, clazz, mrb_intern(mrb, ">>"), mrb_intern(mrb, "remove"));
}
