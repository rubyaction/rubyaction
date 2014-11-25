#ifndef __PHYSICS_WORLD__
#define __PHYSICS_WORLD__

#include "EventDispatcher.hpp"
#include "physics/Body.hpp"

namespace RubyAction
{
namespace Physics
{

  class World : public EventDispatcher,
                public b2ContactListener,
                public b2RayCastCallback
  {
  private:
    b2World* world;
    mrb_value raycastCallback;
  public:
    World(mrb_value, int, int, bool);
    virtual ~World();
    void clearForces();
    Body* createBody(mrb_value);
    int* getGravity();
    void setGravity(int, int);
    void raycast(int, int, int, int, mrb_value);
    void step(float, int, int);

    // Box2D callbacks

    // b2ContactListener
    virtual void BeginContact(b2Contact*);
    virtual void EndContact(b2Contact*);

    // b2RayCastCallback
    virtual float32 ReportFixture(b2Fixture*, const b2Vec2&, const b2Vec2&, float32);
  };

  void bindWorld(mrb_state*, RClass*, RClass*);

}
}

#endif // __PHYSICS_WORLD__
