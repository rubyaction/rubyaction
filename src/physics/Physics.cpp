#include "physics/Physics.hpp"
#include "physics/World.hpp"
#include "physics/Body.hpp"
#include "physics/DebugDraw.hpp"


namespace RubyAction
{
namespace Physics
{

  void bind(mrb_state *mrb, RClass *module)
  {
    struct RClass *physics = mrb_define_module_under(mrb, module, "Physics");
    bindWorld(mrb, module, physics);
    bindBody(mrb, module, physics);
    bindDebugDraw(mrb, module, physics);
  }

}
}
