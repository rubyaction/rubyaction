#include "physics/World.hpp"
#include "RubyEngine.hpp"
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/variable.h>

namespace RubyAction
{
namespace Physics
{

  World::World(mrb_value self, int gravityx, int gravity, bool doSleep)
    : EventDispatcher(self)
  {
    this->world = new b2World(b2Vec2(gravityx, gravity));
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

  void World::BeginContact(b2Contact* contact)
  {
    mrb_state *mrb = RubyEngine::getInstance()->getState();
    mrb_value data[] = { mrb_fixnum_value(1), mrb_fixnum_value(2) };
    this->dispatch(mrb_intern(mrb, "begin_contact"), data, 2);
  }

  void World::EndContact(b2Contact* contact)
  {
    mrb_state *mrb = RubyEngine::getInstance()->getState();
    mrb_value data[] = { mrb_fixnum_value(1), mrb_fixnum_value(2) };
    this->dispatch(mrb_intern(mrb, "end_contact"), data, 2);
  }

  static mrb_value World_initialize(mrb_state *mrb, mrb_value self)
  {
    mrb_int gravityx;
    mrb_int gravityY;
    mrb_bool doSleep;
    int argc = mrb_get_args(mrb, "ii|b", &gravityx, &gravityY, &doSleep);

    if (argc == 2) doSleep = true;

    SET_INSTANCE(self, new World(self, gravityx, gravityY, doSleep));
    return self;
  }

  static mrb_value World_clearForces(mrb_state *mrb, mrb_value self)
  {
    GET_INSTANCE(self, world, World)
    world->clearForces();
    return self;
  }

  void bindWorld(mrb_state *mrb, RClass *module, RClass *physics)
  {
    struct RClass *super = mrb_class_get_under(mrb, module, "EventDispatcher");
    struct RClass *clazz = mrb_define_class_under(mrb, physics, "World", super);
    MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

    mrb_define_method(mrb, clazz, "initialize", World_initialize, MRB_ARGS_ARG(2, 1));
    mrb_define_method(mrb, clazz, "clear_forces", World_clearForces, MRB_ARGS_NONE());
  }

}
}
