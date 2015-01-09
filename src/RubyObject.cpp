#include "RubyObject.hpp"
#include <iostream>

using namespace RubyAction;
using namespace std;

int RubyObject::instances = 0;

RubyObject::RubyObject(mrb_value self)
  : self(self),
    mrb(RubyEngine::getInstance()->getState())
{
  RubyObject::instances++;
}

RubyObject::~RubyObject()
{
  RubyObject::instances--;
}

mrb_value RubyObject::getProperty(const char *property)
{
  return mrb_iv_get(mrb, self, mrb_intern(mrb, property));
}

void RubyObject::setProperty(const char *property, mrb_value value)
{
  mrb_iv_set(mrb, self, mrb_intern(mrb, property), value);
}

RubyObject* RubyObject::getObject(const char *property)
{
  return unwrap<RubyObject>(getProperty(property));
}

const char * RubyObject::inspect()
{
  return mrb_string_value_ptr(mrb, mrb_inspect(mrb, self));
}

void RubyObject::setSelf(mrb_value self)
{
  this->self = self;
}

mrb_value RubyObject::getSelf()
{
  return self;
}
