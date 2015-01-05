#ifndef __APPLICATION__
#define __APPLICATION__

#include <SFML/Graphics.hpp>

namespace RubyAction
{

  class Application
  {
  private:
    static Application *instance;
    Application() {}

  public:
    sf::RenderWindow *window;
    static Application* getInstance();
    int run(const char *);

    struct {
      int width = 800;
      int height = 600;
      const char *title = "RubyAction";
    } config;
  };

}

#endif // __APPLICATION__
