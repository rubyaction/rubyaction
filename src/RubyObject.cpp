#include "RubyObject.hpp"
#include <iostream>

namespace RubyAction
{

  struct mrb_data_type mrb_ruby_object_binding = { "RubyObject", mrb_ruby_object_free };

  RubyObject::RubyObject(mrb_value self)
    : self(self)
  {
    std::cout << "Created: " << this->inspect() << std::endl;
  }

  RubyObject::~RubyObject()
  {
    std::cout << "Destroyed: " << this->inspect() << std::endl;
  }

  const char * RubyObject::inspect()
  {
    mrb_state *mrb = RubyEngine::getInstance()->getState();
    return mrb_string_value_ptr(mrb, mrb_inspect(mrb, self));
  }

}
