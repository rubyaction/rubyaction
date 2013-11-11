#include "Application.hpp"
#include "FPSManager.hpp"
#include "RubyEngine.hpp"
#include "EventDispatcher.hpp"
#include "TextureBase.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Bitmap.hpp"
#include "TextureRegion.hpp"
#include "Stage.hpp"
#include "BaseFont.hpp"
#include "Font.hpp"
#include "TTFont.hpp"
#include "TextField.hpp"
#include "physics/Physics.hpp"

#include <sstream>
#include <mruby.h>
#include <mruby/value.h>
#include <mruby/hash.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

using namespace RubyAction;

void mouseMoveEvent(SDL_Event *event)
{
  mrb_state *mrb = RubyEngine::getInstance()->getState();
  mrb_value data[] = {
    mrb_fixnum_value(event->motion.x),
    mrb_fixnum_value(event->motion.y)
  };
  Stage::getInstance()->dispatch(mrb_intern(mrb, "mouse_move"), data, 2);
}

void mouseButtonEvent(SDL_Event *event, const char *name)
{
  mrb_state *mrb = RubyEngine::getInstance()->getState();
  mrb_value data[] = {
    mrb_fixnum_value(event->button.button),
    mrb_fixnum_value(event->button.x),
    mrb_fixnum_value(event->button.y)
  };
  Stage::getInstance()->dispatch(mrb_intern(mrb, name), data, 3);
}

void processInputEvents(SDL_Event *event)
{
  switch (event->type)
  {
    case SDL_MOUSEMOTION:
      mouseMoveEvent(event);
      break;
    case SDL_MOUSEBUTTONDOWN:
      mouseButtonEvent(event, "mouse_down");
      break;
    case SDL_MOUSEBUTTONUP:
      mouseButtonEvent(event, "mouse_up");
      break;
  }
}

Application *Application::instance = new Application();

Application* Application::getInstance()
{
  return instance;
}

int Application::run(const char *filename)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    LOG(SDL_GetError());
    return -1;
  }

  if (TTF_Init() < 0)
  {
    LOG(SDL_GetError());
    return -1;
  }

  int flags = IMG_INIT_JPG | IMG_INIT_PNG;
  int initted = IMG_Init(flags);
  if ((initted & flags) != flags)
  {
    LOG(IMG_GetError());
    return -1;
  }

  int x = SDL_WINDOWPOS_CENTERED, y = SDL_WINDOWPOS_CENTERED, width = config.width, height = config.height;
  window = SDL_CreateWindow(config.title, x, y, width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  RubyAction::RubyEngine *engine = RubyAction::RubyEngine::getInstance();
  engine->bind(RubyAction::bindEventDispatcher);
  engine->bind(RubyAction::bindTextureBase);
  engine->bind(RubyAction::bindTexture);
  engine->bind(RubyAction::bindSprite);
  engine->bind(RubyAction::bindBitmap);
  engine->bind(RubyAction::bindTextureRegion);
  engine->bind(RubyAction::bindStage);
  engine->bind(RubyAction::bindBaseFont);
  engine->bind(RubyAction::bindFont);
  engine->bind(RubyAction::bindTTFont);
  engine->bind(RubyAction::bindTextField);
  engine->bind(RubyAction::Physics::bind);

  if (!engine->load(filename)) return -1;

  FPSManager fps(config.fps);

  bool running = true;
  SDL_Event event;

  while (running)
  {
    int arena = mrb_gc_arena_save(engine->getState());

    while(SDL_PollEvent(&event)) {
      switch (event.type)
      {
        case SDL_QUIT:
          running = false;
          break;
        default:
          processInputEvents(&event);
      }
    }

    mrb_value delta = mrb_float_value(engine->getState(), fps.step());
    Stage::getInstance()->dispatch(mrb_intern(engine->getState(), "enter_frame"), &delta, 1);

    SDL_RenderClear(renderer);
    Stage::getInstance()->render(renderer);
    SDL_RenderPresent(renderer);

    mrb_gc_arena_restore(engine->getState(), arena);

    engine->garbageCollect();

    std::stringstream newTitle;
    newTitle << config.title << " | FPS: " << fps.getAverageFPS();
    SDL_SetWindowTitle(window, newTitle.str().c_str());
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return 0;
}

SDL_Window* Application::getWindow()
{
  return window;
}

SDL_Renderer* Application::getRenderer()
{
  return renderer;
}
