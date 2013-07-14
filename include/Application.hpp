#ifndef __APPLICATION__
#define __APPLICATION__

namespace RubyAction
{

  class Application
  {
  private:
    static Application *instance;
    Application() {}
    void update();
    void draw();

  public:
    static Application* getInstance();
    int run(const char *);

    struct {
      int width = 800;
      int height = 600;
      const char *title = "alpha";
      int fps = 60;
    } config;
  };

}

#endif // __APPLICATION__
