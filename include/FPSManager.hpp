#ifndef __FPS_MANAGER__
#define __FPS_MANAGER__

#include <SDL2_framerate.h>

namespace RubyAction
{

  class FPSManager
  {
  private:
    FPSmanager manager;
    int counter;
    int startTicks;
  public:
    FPSManager(int=60);
    float step();
    int getTargetFPS();
    int getAverageFPS();
  };

}

#endif // __FPS_MANAGER__
