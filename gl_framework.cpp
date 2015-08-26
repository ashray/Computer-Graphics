#include "gl_framework.hpp"

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }

  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }

  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }

  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // Should enable modelling mode
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
      current_system_state = 0;
      std::cout << "In modelling mode!" << std::endl;
    }

    // Should enable modelling mode
    if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
      current_system_state = 1;
      std::cout << "In inspection mode!" << std::endl;
    }
  }

  //!GLFW mouse callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && current_system_state==0)
    {
      double xpos;
      double ypos;
      glfwGetCursorPos (window, &xpos, &ypos);
      std::cout << "Cursor positions are: (" <<  xpos << ", " << ypos << ")\n";
      push_vertex(xpos, ypos, glm::vec4(0.5,0.5,0.5,1.0));
    }
  }
};
