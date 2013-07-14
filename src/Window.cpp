#include "Window.hpp"
#include <iostream>


namespace RubyAction
{

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  }

  Window::Window(int width, int height, const char *title)
  {
    if (!glfwInit()) exit(EXIT_FAILURE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window) exit(EXIT_FAILURE);

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
  }

  void Window::update()
  {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  bool Window::isOpen()
  {
    return !glfwWindowShouldClose(window);
  }

}
