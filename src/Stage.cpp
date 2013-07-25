#include "Stage.hpp"
#include "RubyEngine.hpp"
#include <mruby/variable.h>
#include <mruby/array.h>

namespace RubyAction
{

  Stage *Stage::instance = new Stage();

  Stage* Stage::getInstance()
  {
    return instance;
  }

  void Stage::setSelf(mrb_value self)
  {
    this->self = self;
  }

  void Stage::render(SDL_Renderer *renderer)
  {
    mrb_state *mrb = RubyEngine::getInstance()->getState();
    mrb_value children = getProperty("children");

    for (int i = 0; i < RARRAY_LEN(children); i++)
    {
      mrb_value child = mrb_ary_ref(mrb, children, i);
      GET_INSTANCE(child, sprite, Sprite)
      sprite->render(renderer);
    }
  }

  void bindStage(mrb_state *mrb, RClass *module)
  {
    mrb_value stage = RubyEngine::getInstance()->newInstance("Sprite", 0, NULL);
    mrb_define_const(mrb, module, "Stage", stage);

    Stage::getInstance()->setSelf(stage);
    SET_INSTANCE(stage, Stage::getInstance());
  }

}
