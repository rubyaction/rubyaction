#include "RubyEngine.hpp"
#include "EventDispatcher.hpp"

int main(int argc, const char **argv)
{
  const char *filename = (argc > 1) ? argv[1] : "main.rb";

  RubyAction::RubyEngine *engine = RubyAction::RubyEngine::getInstance();
  engine->bind(RubyAction::bindEventDispatcher);
  engine->load(filename);

  return 0;
}

