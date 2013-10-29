#include "physics/Physics.hpp"

namespace RubyAction
{
namespace Physics
{

  void bind(mrb_state *mrb, RClass *module)
  {
    struct RClass *physics = mrb_define_module_under(mrb, module, "Physics");
  }

}
}
