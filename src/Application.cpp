#include "Application.hpp"
#include "Clock.hpp"
#include "Window.hpp"
#include "RubyEngine.hpp"
#include "EventDispatcher.hpp"


namespace RubyAction
{

  Application *Application::instance = new Application();

  Application* Application::getInstance()
  {
    return instance;
  }

  int Application::run(const char *filename)
  {
    Window window = Window(config.width, config.height, config.title);
    Clock clock = Clock(config.fps);

    if (window.isOpen())
    {

      RubyAction::RubyEngine *engine = RubyAction::RubyEngine::getInstance();
      engine->bind(RubyAction::bindEventDispatcher);
      engine->load(filename);

      // glMatrixMode(GL_PROJECTION);
      // glLoadIdentity();
      // glOrtho(0, config.width, config.height, 0, 0, 1);
      // glMatrixMode(GL_MODELVIEW);

      // glEnable(GL_TEXTURE_2D);
      // glDisable(GL_DEPTH_TEST);
      // glDisable(GL_LIGHTING);
      // glEnable(GL_BLEND);
      // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


      while (window.isOpen())
      {
        // glClear(GL_COLOR_BUFFER_BIT);
        // sceneManager->update();
        // sceneManager->draw();
        window.update();
        engine->garbageCollect();
        clock.tick();
      }
    }

    return 0;
  }

}
