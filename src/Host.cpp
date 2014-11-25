#include "Application.hpp"

int main(int argc, const char **argv)
{
  RubyAction::Application *app = RubyAction::Application::getInstance();

  app->config.width = 800;
  app->config.height = 600;
  app->config.title = "RubyAction";

  return app->run((argc > 1) ? argv[1] : "main.rb");
}
