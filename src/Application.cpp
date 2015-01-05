#include "Application.hpp"
#include "RubyEngine.hpp"
#include "EventDispatcher.hpp"
#include "TextureBase.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Bitmap.hpp"
#include "TextureRegion.hpp"
#include "Stage.hpp"
#include "FontBase.hpp"
#include "Font.hpp"
#include "TTFont.hpp"
#include "TextField.hpp"
#include "physics/Physics.hpp"

#include <sstream>
#include <iomanip>
#include <mruby.h>
#include <mruby/value.h>
#include <mruby/hash.h>

using namespace RubyAction;

// void mouseMoveEvent(SDL_Event *event)
// {
//   mrb_state *mrb = RubyEngine::getInstance()->getState();
//   mrb_value data[] = {
//     mrb_fixnum_value(event->motion.x),
//     mrb_fixnum_value(event->motion.y)
//   };
//   Stage::getInstance()->dispatch(mrb_intern(mrb, "mouse_move"), data, 2);
// }

// void mouseButtonEvent(SDL_Event *event, const char *name)
// {
//   mrb_state *mrb = RubyEngine::getInstance()->getState();
//   mrb_value data[] = {
//     mrb_fixnum_value(event->button.button),
//     mrb_fixnum_value(event->button.x),
//     mrb_fixnum_value(event->button.y)
//   };
//   Stage::getInstance()->dispatch(mrb_intern(mrb, name), data, 3);
// }

// void keyEvent(SDL_Event *event, const char *name)
// {
//   mrb_state *mrb = RubyEngine::getInstance()->getState();
//   mrb_value data = mrb_str_new_cstr(mrb, SDL_GetKeyName(event->key.keysym.sym));
//   Stage::getInstance()->dispatch(mrb_intern(mrb, name), &data, 1);
// }

// void processInputEvents(SDL_Event *event)
// {
//   switch (event->type)
//   {
//     case SDL_MOUSEMOTION:
//       mouseMoveEvent(event);
//       break;
//     case SDL_MOUSEBUTTONDOWN:
//       mouseButtonEvent(event, "mouse_down");
//       break;
//     case SDL_MOUSEBUTTONUP:
//       mouseButtonEvent(event, "mouse_up");
//       break;
//     case SDL_KEYDOWN:
//       keyEvent(event, "key_down");
//       break;
//     case SDL_KEYUP:
//       keyEvent(event, "key_up");
//       break;
//   }
// }

Application *Application::instance = new Application();

Application* Application::getInstance()
{
  return instance;
}

int Application::run(const char *filename)
{
  window = new sf::RenderWindow(sf::VideoMode(config.width, config.height), config.title);

  RubyAction::RubyEngine *engine = RubyAction::RubyEngine::getInstance();
  engine->bind(RubyAction::bindEventDispatcher);
  engine->bind(RubyAction::bindTextureBase);
  engine->bind(RubyAction::bindTexture);
  engine->bind(RubyAction::bindSprite);
  engine->bind(RubyAction::bindBitmap);
  engine->bind(RubyAction::bindTextureRegion);
  engine->bind(RubyAction::bindStage);
  engine->bind(RubyAction::bindFontBase);
  engine->bind(RubyAction::bindFont);
  engine->bind(RubyAction::bindTTFont);
  engine->bind(RubyAction::bindTextField);
  engine->bind(RubyAction::Physics::bind);

  if (!engine->load(filename)) return -1;

  sf::Clock clock;
  sf::Transform identity = sf::Transform::Identity;

  while (window->isOpen())
  {
    int arena = mrb_gc_arena_save(engine->getState());

    // Process events
    sf::Event event;
    while (window->pollEvent(event))
    {
      // Close window: exit
      if (event.type == sf::Event::Closed)
      {
        window->close();
      }
      else if (event.type == sf::Event::MouseButtonPressed)
      {
        mrb_state *mrb = RubyEngine::getInstance()->getState();
        mrb_value data[] = {
          mrb_fixnum_value(event.mouseButton.button),
          mrb_fixnum_value(event.mouseButton.x),
          mrb_fixnum_value(event.mouseButton.y)
        };
        const char *name = (event.type == sf::Event::MouseButtonPressed) ? "mouse_down" : "mouse_up";
        Stage::getInstance()->dispatch(mrb_intern(mrb, name), data, 3);
      }
    }

    mrb_value delta = mrb_float_value(engine->getState(), clock.restart().asSeconds());
    Stage::getInstance()->dispatch(mrb_intern(engine->getState(), "enter_frame"), &delta, 1);

    window->clear();
    Stage::getInstance()->render(window, &identity);
    window->display();

    mrb_gc_arena_restore(engine->getState(), arena);

    engine->garbageCollect();

    // if (SDL_GetTicks() > nextFPSUpdate)
    // {
    //   std::stringstream newTitle;
    //   newTitle << config.title << " | FPS: " << std::setprecision(3) << (1.0 / dt);
    //   SDL_SetWindowTitle(window, newTitle.str().c_str());
    //   nextFPSUpdate = SDL_GetTicks() + 1000;
    // }
  }

  window->close();
  delete window;
  return 0;
}
