#include "physics/Body.hpp"
#include <mruby/hash.h>
#include <mruby/array.h>


#define GET_VALUE(key) mrb_hash_get(mrb, hash, mrb_symbol_value(mrb_intern(mrb, key)))

namespace RubyAction
{
namespace Physics
{

  Body::Body(b2World* world, mrb_value hash)
    : RubyObject(mrb_nil_value())
  {
    RubyEngine *engine = RubyEngine::getInstance();
    RClass *clazz = mrb_class_get_under(mrb, engine->getClass("Physics"), "Body");
    this->self = engine->newInstance(clazz, 0, NULL, false);

    b2BodyDef def;

    mrb_value type = GET_VALUE("type");
    switch(mrb_fixnum(type)) {
      case 0: def.type = b2_staticBody;
      case 1: def.type = b2_kinematicBody;
      case 2: def.type = b2_dynamicBody;
    }

    mrb_value position = GET_VALUE("position");
    if (!mrb_nil_p(position)) def.position.Set(
      mrb_float(mrb_ary_ref(mrb, position, 0)),
      mrb_float(mrb_ary_ref(mrb, position, 1))
    );

    mrb_value angle = GET_VALUE("angle");
    if (!mrb_nil_p(angle)) def.angle = mrb_float(angle);

    mrb_value linearVelocity = GET_VALUE("linear_velocity");
    if (!mrb_nil_p(linearVelocity)) def.linearVelocity.Set(
      mrb_float(mrb_ary_ref(mrb, linearVelocity, 0)),
      mrb_float(mrb_ary_ref(mrb, linearVelocity, 1))
    );

    mrb_value angularVelocity = GET_VALUE("angular_velocity");
    if (!mrb_nil_p(angularVelocity)) def.angularVelocity = mrb_float(angularVelocity);

    mrb_value linearDamping = GET_VALUE("linear_damping");
    if (!mrb_nil_p(linearDamping)) def.linearDamping = mrb_float(linearDamping);

    mrb_value angularDamping = GET_VALUE("angular_damping");
    if (!mrb_nil_p(angularDamping)) def.angularDamping = mrb_float(angularDamping);

    mrb_value allowSleep = GET_VALUE("allow_sleep");
    if (!mrb_nil_p(allowSleep)) def.allowSleep = mrb_bool(allowSleep);

    mrb_value awake = GET_VALUE("awake");
    if (!mrb_nil_p(awake)) def.awake = mrb_bool(awake);

    mrb_value fixedRotation = GET_VALUE("fixed_rotation");
    if (!mrb_nil_p(fixedRotation)) def.fixedRotation = mrb_bool(fixedRotation);

    mrb_value bullet = GET_VALUE("bullet");
    if (!mrb_nil_p(bullet)) def.bullet = mrb_bool(bullet);

    mrb_value active = GET_VALUE("active");
    if (!mrb_nil_p(active)) def.active = mrb_bool(active);

    mrb_value gravityScale = GET_VALUE("gravity_scale");
    if (!mrb_nil_p(gravityScale)) def.gravityScale = mrb_float(gravityScale);

    this->body = world->CreateBody(&def);
  }

  static mrb_value World_initialize(mrb_state *mrb, mrb_value self)
  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Wrong use of this class. Try RubyAction::Physics::World.create_body");
    return self;
  }

  void bindBody(mrb_state *mrb, RClass *module, RClass *physics)
  {
    struct RClass *clazz = mrb_define_class_under(mrb, physics, "Body", mrb->object_class);
    MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

    mrb_define_method(mrb, clazz, "initialize", World_initialize, MRB_ARGS_NONE());

    mrb_define_const(mrb, clazz, "STATIC_BODY", mrb_fixnum_value(0));
    mrb_define_const(mrb, clazz, "KINEMATIC_BODY", mrb_fixnum_value(1));
    mrb_define_const(mrb, clazz, "DYNAMIC_BODY", mrb_fixnum_value(2));
  }

}
}
