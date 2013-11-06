#include "physics/Body.hpp"
#include "util/array.hpp"
#include "util/hash.hpp"
#include <mruby/hash.h>
#include <mruby/array.h>

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

    mrb_value type = H_GET_VALUE_DEF(hash, "type", mrb_fixnum_value(b2_dynamicBody));
    switch(mrb_fixnum(type)) {
      case 0: def.type = b2_staticBody; break;
      case 1: def.type = b2_kinematicBody; break;
      case 2: def.type = b2_dynamicBody;
    }

    mrb_value position = H_GET_VALUE(hash, "position");
    if (!mrb_nil_p(position)) def.position.Set(
      A_GET_FLOAT(position, 0),
      A_GET_FLOAT(position, 1)
    );

    mrb_value angle = H_GET_VALUE(hash, "angle");
    if (!mrb_nil_p(angle)) def.angle = TO_FLOAT(angle);

    mrb_value linearVelocity = H_GET_VALUE(hash, "linear_velocity");
    if (!mrb_nil_p(linearVelocity)) def.linearVelocity.Set(
      A_GET_FLOAT(linearVelocity, 0),
      A_GET_FLOAT(linearVelocity, 1)
    );

    mrb_value angularVelocity = H_GET_VALUE(hash, "angular_velocity");
    if (!mrb_nil_p(angularVelocity)) def.angularVelocity = TO_FLOAT(angularVelocity);

    mrb_value linearDamping = H_GET_VALUE(hash, "linear_damping");
    if (!mrb_nil_p(linearDamping)) def.linearDamping = TO_FLOAT(linearDamping);

    mrb_value angularDamping = H_GET_VALUE(hash, "angular_damping");
    if (!mrb_nil_p(angularDamping)) def.angularDamping = TO_FLOAT(angularDamping);

    mrb_value allowSleep = H_GET_VALUE(hash, "allow_sleep");
    if (!mrb_nil_p(allowSleep)) def.allowSleep = mrb_bool(allowSleep);

    mrb_value awake = H_GET_VALUE(hash, "awake");
    if (!mrb_nil_p(awake)) def.awake = mrb_bool(awake);

    mrb_value fixedRotation = H_GET_VALUE(hash, "fixed_rotation");
    if (!mrb_nil_p(fixedRotation)) def.fixedRotation = mrb_bool(fixedRotation);

    mrb_value bullet = H_GET_VALUE(hash, "bullet");
    if (!mrb_nil_p(bullet)) def.bullet = mrb_bool(bullet);

    mrb_value active = H_GET_VALUE(hash, "active");
    if (!mrb_nil_p(active)) def.active = mrb_bool(active);

    mrb_value gravityScale = H_GET_VALUE(hash, "gravity_scale");
    if (!mrb_nil_p(gravityScale)) def.gravityScale = TO_FLOAT(gravityScale);

    this->body = world->CreateBody(&def);

    // b2CircleShape circle;
    // circle.m_radius = 60;
    // this->body->CreateFixture(&circle, 1);

    // b2PolygonShape box;
    // box.SetAsBox(80, 40);
    // b2Fixture *fixture = this->body->CreateFixture(&box, 1);
    // fixture->SetRestitution(1.f);

    // def.type = b2_staticBody;
    // def.position.Set(297, 300);
    // this->body = world->CreateBody(&def);

    // box.SetAsBox(100, 10);
    // this->body->CreateFixture(&box, 1);

  }

  static mrb_value Body_initialize(mrb_state *mrb, mrb_value self)
  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Wrong use of this class. Try RubyAction::Physics::World.create_body");
    return self;
  }

  void bindBody(mrb_state *mrb, RClass *module, RClass *physics)
  {
    struct RClass *clazz = mrb_define_class_under(mrb, physics, "Body", mrb->object_class);
    MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

    mrb_define_method(mrb, clazz, "initialize", Body_initialize, MRB_ARGS_NONE());

    mrb_define_const(mrb, clazz, "STATIC_BODY", mrb_fixnum_value(0));
    mrb_define_const(mrb, clazz, "KINEMATIC_BODY", mrb_fixnum_value(1));
    mrb_define_const(mrb, clazz, "DYNAMIC_BODY", mrb_fixnum_value(2));
  }

}
}
