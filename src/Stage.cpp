#include "Stage.hpp"
#include "RubyEngine.hpp"
#include <mruby/variable.h>
#include <mruby/array.h>
#include <mruby/hash.h>

using namespace RubyAction;

Stage *Stage::instance = new Stage();

Stage* Stage::getInstance()
{
  return instance;
}

void Stage::addChild(mrb_value child)
{
  if (!contains(child))
  {
    Sprite::addChild(child);
    GET_INSTANCE(child, childSprite, Sprite)
    childSprite->dispatch(mrb_intern(mrb, "added_to_stage"), NULL, 0);
  }
}

void Stage::removeChild(mrb_value child)
{
  if (contains(child))
  {
    Sprite::removeChild(child);
    GET_INSTANCE(child, childSprite, Sprite)
    childSprite->dispatch(mrb_intern(mrb, "removed_from_stage"), NULL, 0);
  }
}

void RubyAction::bindStage(mrb_state *mrb, RClass *module)
{
  mrb_value stage = RubyEngine::getInstance()->newInstance("Sprite", 0, NULL);
  mrb_define_const(mrb, module, "Stage", stage);

  Stage::getInstance()->setSelf(stage);
  SET_INSTANCE(stage, Stage::getInstance());
}
