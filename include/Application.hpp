#ifndef __APPLICATION__
#define __APPLICATION__

#include <SDL.h>

namespace RubyAction
{

  class Application
  {
  private:
    static Application *instance;
    Application() {}
    SDL_Window *window;
    SDL_Renderer *renderer;

  public:
    static Application* getInstance();
    int run(const char *);
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

    struct {
      int width = 800;
      int height = 600;
      const char *title = "alpha";
      int fps = 60;
    } config;
  };

}

#endif // __APPLICATION__
