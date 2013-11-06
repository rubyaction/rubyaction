#include "Application.hpp"
#include "RubyEngine.hpp"
#include "EventDispatcher.hpp"
#include "TextureBase.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Bitmap.hpp"
#include "TextureRegion.hpp"
#include "Stage.hpp"
#include <iostream>
#include <mruby.h>
#include <mruby/value.h>
#include <mruby/hash.h>

namespace RubyAction
{

  static const int RUN_GAME_LOOP = 1;

  Uint32 timerUpdate(Uint32 interval, void *param)
  {
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = RUN_GAME_LOOP;
    event.user.data1 = &interval;
    SDL_PushEvent(&event);
    return interval;
  }

  void mouseMoveEvent(SDL_Event *event)
  {
    mrb_state *mrb = RubyEngine::getInstance()->getState();
    mrb_value data[] = { mrb_fixnum_value(event->motion.x), mrb_fixnum_value(event->motion.y) };
    Stage::getInstance()->dispatch(mrb_intern(mrb, "mouse_move"), data, 2);
  }

  void mouseButtonEvent(SDL_Event *event, const char *name)
  {
    mrb_state *mrb = RubyEngine::getInstance()->getState();
    mrb_value data = mrb_fixnum_value(event->button.button);
    Stage::getInstance()->dispatch(mrb_intern(mrb, name), &data, 1);
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
    RubyAction::RubyEngine *engine = RubyAction::RubyEngine::getInstance();
    engine->bind(RubyAction::bindEventDispatcher);
    engine->bind(RubyAction::bindTextureBase);
    engine->bind(RubyAction::bindTexture);
    engine->bind(RubyAction::bindSprite);
    engine->bind(RubyAction::bindBitmap);
    engine->bind(RubyAction::bindTextureRegion);
    engine->bind(RubyAction::bindStage);
    if (!engine->load(filename)) return -1;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
      std::cout << SDL_GetError() << std::endl;
      return -1;
    }

    int x = SDL_WINDOWPOS_CENTERED, y = SDL_WINDOWPOS_CENTERED, width = config.width, height = config.height;

    window = SDL_CreateWindow(config.title, x, y, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_AddTimer(1000 / 60, timerUpdate, NULL);

    bool running = true;
    SDL_Event event;

    while (running && SDL_WaitEvent(&event))
    {
      switch (event.type)
      {
        case SDL_USEREVENT:
          if (event.user.code == RUN_GAME_LOOP)
          {
            mrb_value delta = mrb_fixnum_value(*((Uint32*) event.user.data1));
            Stage::getInstance()->dispatch(mrb_intern(engine->getState(), "enter_frame"), &delta, 1);

            SDL_RenderClear(renderer);
            Stage::getInstance()->render(renderer);
            SDL_RenderPresent(renderer);

            engine->garbageCollect();
          }
          break;
        case SDL_QUIT:
          running = false;
          break;
        default:
          processInputEvents(&event);
      }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

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

}
