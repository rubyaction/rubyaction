#include "FPSManager.hpp"

using namespace RubyAction;

FPSManager::FPSManager(int fps)
  : counter(0),
    startTicks(SDL_GetTicks())
{
  SDL_initFramerate(&manager);
  SDL_setFramerate(&manager, fps);
}

float FPSManager::step()
{
  ++counter;
  return SDL_framerateDelay(&manager) / 1000.f;
}

int FPSManager::getTargetFPS()
{
  return SDL_getFramerate(&manager);
}

int FPSManager::getAverageFPS()
{
  float time = (SDL_GetTicks() - startTicks) / 1000.f;
  return counter / time;
}
