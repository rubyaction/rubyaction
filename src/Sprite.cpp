#include "Sprite.hpp"
#include "RubyEngine.hpp"
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/variable.h>

namespace RubyAction
{

  Sprite::Sprite(mrb_value self)
    : EventDispatcher(self),
      x(0),
      y(0),
      width(0),
      height(0),
      scaleX(0),
      scaleY(0),
      rotation(0),
      visible(true)
  {
  }

  int Sprite::getX()
  {
    return x;
  }

  void Sprite::setX(int x)
  {
    this->x = x;
  }

  int Sprite::getY()
  {
    return y;
  }

  void Sprite::setY(int y)
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

  void Sprite::render(SDL_Renderer *renderer)
  {
  }

  void Sprite::addChild(mrb_value child)
  {
    mrb_state *mrb = RubyEngine::getInstance()->getState();
    mrb_value children = mrb_iv_get(mrb, self, mrb_intern(mrb, "children"));

    for (int i = 0; i < RARRAY_LEN(children); i++)
    {
      mrb_value current = mrb_ary_ref(mrb, children, i);
      if (mrb_obj_equal(mrb, child, current)) return;
    }

    mrb_ary_push(mrb, children, child);
  }

  void Sprite::removeChild(mrb_value child)
  {
    mrb_state *mrb = RubyEngine::getInstance()->getState();
    mrb_value old = mrb_iv_get(mrb, self, mrb_intern(mrb, "children"));
    mrb_value children = mrb_ary_new(mrb);

    for (int i = 0; i < RARRAY_LEN(old); i++)
    {
      mrb_value current = mrb_ary_ref(mrb, old, i);
      if (!mrb_obj_equal(mrb, child, current)) mrb_ary_push(mrb, children, current);
    }

    mrb_iv_set(mrb, self, mrb_intern(mrb, "children"), children);
  }

  static mrb_value Sprite_initialize(mrb_state *mrb, mrb_value self)
  {
    mrb_value children = mrb_ary_new(mrb);
    mrb_iv_set(mrb, self, mrb_intern(mrb, "children"), children);

    SET_INSTANCE(new Sprite(self));
    return self;
  }

  static mrb_value Sprite_getX(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(Sprite)
    return mrb_fixnum_value(instance->getX());
  }

  static mrb_value Sprite_setX(mrb_state *mrb, mrb_value self)
  {
    mrb_int x;
    mrb_get_args(mrb, "i", &x);

    GET_INSTANCE(Sprite)
    instance->setX(x);
    return self;
  }

  static mrb_value Sprite_getY(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(Sprite)
    return mrb_fixnum_value(instance->getY());
  }

  static mrb_value Sprite_setY(mrb_state *mrb, mrb_value self)
  {
    mrb_int y;
    mrb_get_args(mrb, "i", &y);

    GET_INSTANCE(Sprite)
    instance->setY(y);
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

    GET_INSTANCE(Sprite)
    instance->setX(mrb_fixnum(mrb_ary_ref(mrb, position, 0)));
    instance->setY(mrb_fixnum(mrb_ary_ref(mrb, position, 1)));
    return self;
  }

  static mrb_value Sprite_getWidth(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(Sprite)
    return mrb_fixnum_value(instance->getWidth());
  }

  static mrb_value Sprite_setWidth(mrb_state *mrb, mrb_value self)
  {
    mrb_int width;
    mrb_get_args(mrb, "i", &width);

    GET_INSTANCE(Sprite)
    instance->setWidth(width);
    return self;
  }

  static mrb_value Sprite_getHeight(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(Sprite)
    return mrb_fixnum_value(instance->getHeight());
  }

  static mrb_value Sprite_setHeight(mrb_state *mrb, mrb_value self)
  {
    mrb_int height;
    mrb_get_args(mrb, "i", &height);

    GET_INSTANCE(Sprite)
    instance->setHeight(height);
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

    GET_INSTANCE(Sprite)
    instance->setWidth(mrb_fixnum(mrb_ary_ref(mrb, size, 0)));
    instance->setHeight(mrb_fixnum(mrb_ary_ref(mrb, size, 1)));
    return self;
  }

  static mrb_value Sprite_getScaleX(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(Sprite)
    return mrb_float_value(mrb, instance->getScaleX());
  }

  static mrb_value Sprite_setScaleX(mrb_state *mrb, mrb_value self)
  {
    mrb_float scaleX;
    mrb_get_args(mrb, "f", &scaleX);

    GET_INSTANCE(Sprite)
    instance->setScaleX(scaleX);
    return self;
  }

  static mrb_value Sprite_getScaleY(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(Sprite)
    return mrb_float_value(mrb, instance->getScaleY());
  }

  static mrb_value Sprite_setScaleY(mrb_state *mrb, mrb_value self)
  {
    mrb_float scaleY;
    mrb_get_args(mrb, "f", &scaleY);

    GET_INSTANCE(Sprite)
    instance->setScaleY(scaleY);
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

    GET_INSTANCE(Sprite)
    instance->setScaleX(mrb_float(mrb_ary_ref(mrb, scale, 0)));
    instance->setScaleY(mrb_float(mrb_ary_ref(mrb, scale, 1)));
    return self;
  }

  static mrb_value Sprite_getRotation(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(Sprite)
    return mrb_float_value(mrb, instance->getRotation());
  }

  static mrb_value Sprite_setRotation(mrb_state *mrb, mrb_value self)
  {
    mrb_float rotation;
    mrb_get_args(mrb, "f", &rotation);

    GET_INSTANCE(Sprite)
    instance->setRotation(rotation);
    return self;
  }

  static mrb_value Sprite_isVisible(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(Sprite)
    return mrb_bool_value(instance->isVisible());
  }

  static mrb_value Sprite_setVisible(mrb_state *mrb, mrb_value self)
  {
    mrb_bool visible;
    mrb_get_args(mrb, "b", &visible);

    GET_INSTANCE(Sprite)
    instance->setVisible(visible);
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

    GET_INSTANCE(Sprite)
    instance->addChild(child);
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

    GET_INSTANCE(Sprite)
    instance->removeChild(child);
    return self;
  }

  void bindSprite(mrb_state *mrb, RClass *module)
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
    mrb_define_method(mrb, clazz, "scaleX", Sprite_getScaleX, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "scaleX=", Sprite_setScaleX, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "scaleY", Sprite_getScaleY, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "scaleY=", Sprite_setScaleY, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "scale", Sprite_getScale, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "scale=", Sprite_setScale, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "rotation", Sprite_getRotation, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "rotation=", Sprite_setRotation, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "visible?", Sprite_isVisible, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "visible=", Sprite_setVisible, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "addChild", Sprite_addChild, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "removeChild", Sprite_removeChild, MRB_ARGS_REQ(1));

    // alias
    mrb_alias_method(mrb, clazz, mrb_intern(mrb, "<<"), mrb_intern(mrb, "addChild"));
  }

}
