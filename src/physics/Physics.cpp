#include "physics/Physics.hpp"
#include "physics/World.hpp"

namespace RubyAction
{
namespace Physics
{

  void bind(mrb_state *mrb, RClass *module)
  {
    struct RClass *physics = mrb_define_module_under(mrb, module, "Physics");
    bindWorld(mrb, module, physics);
  }

}
}
