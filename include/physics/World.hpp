#ifndef __PHYSICS_WORLD__
#define __PHYSICS_WORLD__

#include "EventDispatcher.hpp"
#include <Box2D.h>

namespace RubyAction
{
namespace Physics
{

  class World : public EventDispatcher, public b2ContactListener
  {
  private:
    b2World* world;
  public:
    World(mrb_value, int, int, bool);
    virtual ~World();
    void clearForces();
    int* getGravity();
    void setGravity(int, int);
    void step(float, int, int);

    // Box2D callbacks
    virtual void BeginContact(b2Contact*);
    virtual void EndContact(b2Contact*);
  };

  void bindWorld(mrb_state*, RClass*, RClass*);

}
}

#endif // __PHYSICS_WORLD__
