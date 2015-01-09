#include "physics/World.hpp"
#include <mruby/array.h>

using namespace RubyAction;
using namespace RubyAction::Physics;

World::World(mrb_value self, int gravityx, int gravityy, bool doSleep)
  : EventDispatcher(self)
{
  b2Vec2 gravity(gravityx, gravityy);
  this->world = new b2World(gravity);
  this->world->SetAllowSleeping(doSleep);
}

World::~World()
{
  delete this->world;
}

void World::clearForces()
{
  this->world->ClearForces();
}

Body* World::createBody(mrb_value hash)
{
  return new Body(this->world, hash);
}

int* World::getGravity()
{
  b2Vec2 gravity = this->world->GetGravity();
  return new int[2] { static_cast<int>(gravity.x), static_cast<int>(gravity.y) };
}

void World::setGravity(int gravityx, int gravity)
{
  this->world->SetGravity(b2Vec2(gravityx, gravity));
}

void World::raycast(int x1, int y1, int x2, int y2, mrb_value callback)
{
  this->raycastCallback = callback;
  this->world->RayCast(this, b2Vec2(x1, y1), b2Vec2(x2, y2));
  this->raycastCallback = mrb_nil_value();
}

void World::step(float timeStep, int velocityIterations, int positionIterations)
{
  this->world->Step(timeStep, velocityIterations, positionIterations);
  this->world->DrawDebugData();
}

void World::BeginContact(b2Contact* contact)
{
  mrb_value data[] = { mrb_fixnum_value(1), mrb_fixnum_value(2) };
  this->dispatch(mrb_intern(mrb, "begin_contact"), data, 2);
}

void World::EndContact(b2Contact* contact)
{
  mrb_value data[] = { mrb_fixnum_value(1), mrb_fixnum_value(2) };
  this->dispatch(mrb_intern(mrb, "end_contact"), data, 2);
}

float32 World::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
  int argc = 6;
  mrb_value argv[] = {
    mrb_fixnum_value(182), // TODO: pass fixture object
    mrb_fixnum_value(point.x),
    mrb_fixnum_value(point.y),
    mrb_fixnum_value(normal.x),
    mrb_fixnum_value(normal.y),
    mrb_float_value(mrb, fraction)
  };
  mrb_value report = mrb_yield_argv(mrb, this->raycastCallback, argc, argv);
  return mrb_float(report);
}

static mrb_value World_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int gravityx;
  mrb_int gravityy;
  mrb_bool doSleep;
  int argc = mrb_get_args(mrb, "ii|b", &gravityx, &gravityy, &doSleep);

  if (argc == 2) doSleep = true;

  wrap(self, new World(self, gravityx, gravityy, doSleep));
  return self;
}

static mrb_value World_clearForces(mrb_state *mrb, mrb_value self)
{
  unwrap<World>(self)->clearForces();
  return self;
}

static mrb_value World_createBody(mrb_state *mrb, mrb_value self)
{
  mrb_value hash;
  int argc = mrb_get_args(mrb, "H", &hash);
  return unwrap<World>(self)->createBody(hash)->getSelf();
}

static mrb_value World_getGravity(mrb_state *mrb, mrb_value self)
{
  int* xy = unwrap<World>(self)->getGravity();
  mrb_value gravity[2] = { mrb_fixnum_value(xy[0]), mrb_fixnum_value(xy[1]) };
  delete[] xy;
  return mrb_ary_new_from_values(mrb, 2, gravity);
}

static mrb_value World_setGravity(mrb_state *mrb, mrb_value self)
{
  mrb_value gravity;
  mrb_get_args(mrb, "A", &gravity);

  World* world = unwrap<World>(self);
  world->setGravity(mrb_fixnum(mrb_ary_ref(mrb, gravity, 0)), mrb_fixnum(mrb_ary_ref(mrb, gravity, 1)));
  return self;
}

static mrb_value World_raycast(mrb_state *mrb, mrb_value self)
{
  mrb_int x1;
  mrb_int y1;
  mrb_int x2;
  mrb_int y2;
  mrb_value callback;
  mrb_get_args(mrb, "iiii&", &x1, &y1, &x2, &y2, &callback);

  unwrap<World>(self)->raycast(x1, y1, x2, y2, callback);
  return self;
}

static mrb_value World_step(mrb_state *mrb, mrb_value self)
{
  mrb_float timeStep;
  mrb_int velocityIterations;
  mrb_int positionIterations;
  mrb_get_args(mrb, "fii", &timeStep, &velocityIterations, &positionIterations);

  unwrap<World>(self)->step(timeStep, velocityIterations, positionIterations);
  return self;
}

void Physics::bindWorld(mrb_state *mrb, RClass *module, RClass *physics)
{
  struct RClass *super = mrb_class_get_under(mrb, module, "EventDispatcher");
  struct RClass *clazz = mrb_define_class_under(mrb, physics, "World", super);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  mrb_define_method(mrb, clazz, "initialize", World_initialize, MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, clazz, "clear_forces!", World_clearForces, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "create_body", World_createBody, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "gravity", World_getGravity, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "gravity=", World_setGravity, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "raycast", World_raycast, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, clazz, "step", World_step, MRB_ARGS_REQ(3));
}
