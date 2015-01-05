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
#include "RenderTarget.hpp"
#include "physics/Physics.hpp"

#include <sstream>
#include <iomanip>
#include <mruby.h>
#include <mruby/value.h>
#include <mruby/hash.h>

using namespace RubyAction;

void mouseMoveEvent(sf::Event &event)
{
  mrb_state *mrb = RubyEngine::getInstance()->getState();
  mrb_value data[] = {
    mrb_fixnum_value(event.mouseMove.x),
    mrb_fixnum_value(event.mouseMove.y)
  };
  Stage::getInstance()->dispatch(mrb_intern(mrb, "mouse_move"), data, 2);
}

void mouseButtonEvent(sf::Event &event, const char *name)
{
  mrb_state *mrb = RubyEngine::getInstance()->getState();
  mrb_value data[] = {
    mrb_fixnum_value(event.mouseButton.button),
    mrb_fixnum_value(event.mouseButton.x),
    mrb_fixnum_value(event.mouseButton.y)
  };
  Stage::getInstance()->dispatch(mrb_intern(mrb, name), data, 3);
}

void keyEvent(sf::Event &event, const char *name)
{
  mrb_state *mrb = RubyEngine::getInstance()->getState();
  mrb_value data = mrb_fixnum_value(event.key.code);
  Stage::getInstance()->dispatch(mrb_intern(mrb, name), &data, 1);
}

void processInputEvents(sf::RenderWindow &window)
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::MouseMoved:
        mouseMoveEvent(event);
        break;
      case sf::Event::MouseButtonPressed:
        mouseButtonEvent(event, "mouse_down");
        break;
      case sf::Event::MouseButtonReleased:
        mouseButtonEvent(event, "mouse_up");
        break;
      case sf::Event::KeyPressed:
        keyEvent(event, "key_down");
        break;
      case sf::Event::KeyReleased:
        keyEvent(event, "key_up");
        break;
      default:
        break;
    }
  }
}

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
  engine->bind(RubyAction::bindRenderTarget);
  engine->bind(RubyAction::Physics::bind);

  if (!engine->load(filename)) return -1;

  sf::Clock clock;

  while (window->isOpen())
  {
    int arena = mrb_gc_arena_save(engine->getState());

    processInputEvents(*window);

    mrb_value delta = mrb_float_value(engine->getState(), clock.restart().asSeconds());
    Stage::getInstance()->dispatch(mrb_intern(engine->getState(), "enter_frame"), &delta, 1);

    window->clear();
    Stage::getInstance()->render(window);
    window->display();

    mrb_gc_arena_restore(engine->getState(), arena);

    engine->garbageCollect();
  }

  window->close();
  delete window;
  return 0;
}
