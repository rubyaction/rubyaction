#include "Sprite.hpp"
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace RubyAction
{

  Sprite::Sprite(mrb_value self)
    : EventDispatcher(self),
      x(0),
      y(0),
      width(0),
      height(0),
      scaleX(1),
      scaleY(1),
      rotation(0),
      visible(true)
  {
    if (!mrb_nil_p(self))
    {
      setProperty("children", mrb_ary_new(mrb));
    }
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
    if (!isVisible()) return;

    glPushMatrix();
    glm::mat4 matrix = glm::mat4(1.0);

    glm::mat4 anchor = glm::translate(matrix, glm::vec3(-width / 2, -height / 2, 0.0f));
    glm::mat4 rotate = glm::rotate(matrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 translate = glm::translate(matrix, glm::vec3(x, y, 0));
    glm::mat4 scale = glm::scale(matrix, glm::vec3(scaleX, scaleY, 0));

    glm::mat4 model = translate * (rotate * anchor) * scale;
    glMultMatrixf(glm::value_ptr(model));

    this->renderMe(renderer);

    mrb_value children = getProperty("children");
    for (int i = 0; i < RARRAY_LEN(children); i++)
    {
      mrb_value child = mrb_ary_ref(mrb, children, i);
      GET_INSTANCE(child, sprite, Sprite)
      sprite->render(renderer);
    }

    glPopMatrix();
  }

  void Sprite::addChild(mrb_value child)
  {
    mrb_value children = getProperty("children");

    for (int i = 0; i < RARRAY_LEN(children); i++)
    {
      mrb_value current = mrb_ary_ref(mrb, children, i);
      if (mrb_obj_equal(mrb, child, current)) return;
    }

    mrb_ary_push(mrb, children, child);
  }

  void Sprite::removeChild(mrb_value child)
  {
    mrb_value old = getProperty("children");
    mrb_value children = mrb_ary_new(mrb);

    for (int i = 0; i < RARRAY_LEN(old); i++)
    {
      mrb_value current = mrb_ary_ref(mrb, old, i);
      if (!mrb_obj_equal(mrb, child, current)) mrb_ary_push(mrb, children, current);
    }

    setProperty("children", children);
  }

  void Sprite::dispatch(mrb_sym name, mrb_value* argv, int argc)
  {
    mrb_value children = getProperty("children");

    for (int i = 0; i < RARRAY_LEN(children); i++)
    {
      GET_INSTANCE(mrb_ary_ref(mrb, children, i), child, Sprite)
      child->dispatch(name, argv, argc);
    }

    EventDispatcher::dispatch(name, argv, argc);
  }

  static mrb_value Sprite_initialize(mrb_state *mrb, mrb_value self)
  {
    SET_INSTANCE(self, new Sprite(self));
    return self;
  }

  static mrb_value Sprite_getX(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(self, sprite, Sprite)
    return mrb_fixnum_value(sprite->getX());
  }

  static mrb_value Sprite_setX(mrb_state *mrb, mrb_value self)
  {
    mrb_int x;
    mrb_get_args(mrb, "i", &x);

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setX(x);
    return self;
  }

  static mrb_value Sprite_getY(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(self, sprite, Sprite)
    return mrb_fixnum_value(sprite->getY());
  }

  static mrb_value Sprite_setY(mrb_state *mrb, mrb_value self)
  {
    mrb_int y;
    mrb_get_args(mrb, "i", &y);

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setY(y);
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

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setX(mrb_fixnum(mrb_ary_ref(mrb, position, 0)));
    sprite->setY(mrb_fixnum(mrb_ary_ref(mrb, position, 1)));
    return self;
  }

  static mrb_value Sprite_getWidth(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(self, sprite, Sprite)
    return mrb_fixnum_value(sprite->getWidth());
  }

  static mrb_value Sprite_setWidth(mrb_state *mrb, mrb_value self)
  {
    mrb_int width;
    mrb_get_args(mrb, "i", &width);

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setWidth(width);
    return self;
  }

  static mrb_value Sprite_getHeight(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(self, sprite, Sprite)
    return mrb_fixnum_value(sprite->getHeight());
  }

  static mrb_value Sprite_setHeight(mrb_state *mrb, mrb_value self)
  {
    mrb_int height;
    mrb_get_args(mrb, "i", &height);

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setHeight(height);
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

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setWidth(mrb_fixnum(mrb_ary_ref(mrb, size, 0)));
    sprite->setHeight(mrb_fixnum(mrb_ary_ref(mrb, size, 1)));
    return self;
  }

  static mrb_value Sprite_getScaleX(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(self, sprite, Sprite)
    return mrb_float_value(mrb, sprite->getScaleX());
  }

  static mrb_value Sprite_setScaleX(mrb_state *mrb, mrb_value self)
  {
    mrb_float scaleX;
    mrb_get_args(mrb, "f", &scaleX);

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setScaleX(scaleX);
    return self;
  }

  static mrb_value Sprite_getScaleY(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(self, sprite, Sprite)
    return mrb_float_value(mrb, sprite->getScaleY());
  }

  static mrb_value Sprite_setScaleY(mrb_state *mrb, mrb_value self)
  {
    mrb_float scaleY;
    mrb_get_args(mrb, "f", &scaleY);

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setScaleY(scaleY);
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

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setScaleX(mrb_float(mrb_ary_ref(mrb, scale, 0)));
    sprite->setScaleY(mrb_float(mrb_ary_ref(mrb, scale, 1)));
    return self;
  }

  static mrb_value Sprite_getRotation(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(self, sprite, Sprite)
    return mrb_float_value(mrb, sprite->getRotation());
  }

  static mrb_value Sprite_setRotation(mrb_state *mrb, mrb_value self)
  {
    mrb_float rotation;
    mrb_get_args(mrb, "f", &rotation);

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setRotation(rotation);
    return self;
  }

  static mrb_value Sprite_isVisible(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(self, sprite, Sprite)
    return mrb_bool_value(sprite->isVisible());
  }

  static mrb_value Sprite_setVisible(mrb_state *mrb, mrb_value self)
  {
    mrb_bool visible;
    mrb_get_args(mrb, "b", &visible);

    GET_INSTANCE(self, sprite, Sprite)
    sprite->setVisible(visible);
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

    GET_INSTANCE(self, sprite, Sprite)
    sprite->addChild(child);
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

    GET_INSTANCE(self, sprite, Sprite)
    sprite->removeChild(child);
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
    mrb_define_method(mrb, clazz, "scale_x", Sprite_getScaleX, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "scale_x=", Sprite_setScaleX, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "scale_y", Sprite_getScaleY, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "scale_y=", Sprite_setScaleY, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "scale", Sprite_getScale, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "scale=", Sprite_setScale, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "rotation", Sprite_getRotation, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "rotation=", Sprite_setRotation, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "visible?", Sprite_isVisible, MRB_ARGS_NONE());
    mrb_define_method(mrb, clazz, "visible=", Sprite_setVisible, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "add_child", Sprite_addChild, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, clazz, "remove_child", Sprite_removeChild, MRB_ARGS_REQ(1));

    // alias
    mrb_alias_method(mrb, clazz, mrb_intern(mrb, "<<"), mrb_intern(mrb, "add_child"));
  }

}
