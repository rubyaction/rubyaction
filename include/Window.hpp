#ifndef __WINDOW__
#define __WINDOW__

#include "glfw3.h"

namespace RubyAction
{

  class Window
  {
  private:
    GLFWwindow* window;

  public:
    Window(int width, int height, const char *title);
    void update();
    bool isOpen();
  };

}

#endif // __WINDOW__
