#ifndef __PHYSICS_BODY__
#define __PHYSICS_BODY__

#include "RubyObject.hpp"
#include <mruby.h>
#include <Box2D.h>


namespace RubyAction
{
namespace Physics
{

  enum BodyType
  {
    STATIC_BODY,
    KINEMATIC_BODY,
    DYNAMIC_BODY
  };

  class Body : public RubyObject
  {
  private:
    b2Body* body;
  public:
    Body(b2World*, mrb_value);
  };

  void bindBody(mrb_state*, RClass*, RClass*);

}
}

#endif // __PHYSICS_BODY__
