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

    // Write triangle values to disk
    if (key == GLFW_KEY_K && action == GLFW_PRESS)
    {
      FILE *outputFile;
      std::cout << "Please give a filename: ";
      std::string filename;
      std::cin >> filename;
      filename.append(".raw");
      outputFile = fopen(filename.c_str(), "w");
      for (int i = 0; i<num_vertices; i++)
      {
        fprintf(outputFile, "%lf %lf %lf %lf %lf %lf\n", v_positions[i].x,
          v_positions[i].y, v_positions[i].z,
          v_colors[i].r, v_colors[i].g, v_colors[i].b);
      }
      fclose(outputFile);
      std::cout << "Vertex data successfully exported\n";
    }

    // Loads vertex positions from disk
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
      // We overwrite the existing model
      num_vertices=0;
      double d[6];
      std::cout << "Please give a filename: ";
      std::string filename;
      std::cin >> filename;
      filename.append(".raw");
      FILE* inputFile = fopen(filename.c_str(), "r");
      while(!feof(inputFile))
      {
        fscanf (inputFile, "%lf %lf %lf %lf %lf %lf\n", &d[0], &d[1], &d[2], &d[3], &d[4], &d[5]);
        ensureRoomForVertex();
        v_positions[num_vertices] = glm::vec4(d[0], d[1], d[2], 1);
        v_colors[num_vertices] = glm::vec4(d[3], d[4], d[5], 1);
        num_vertices++;
      }
      fclose(inputFile);
      std::cout << "Loading model successful\n" << std::endl;
    }
  }

  //!GLFW mouse callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
    int getLeftShiftKeyState;
    int getRightShiftKeyState;
    getLeftShiftKeyState = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
    getRightShiftKeyState = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);




    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && current_system_state==0)
    {
      // If key is pressed, then glfwGetKey returns GLFW_RELEASE which is 1. If the key is not pressed it returns 0.
      // Remove the last added point
      if (getLeftShiftKeyState==1 || getRightShiftKeyState==1)
      {
        num_vertices = num_vertices - 1;
      }
      // Add a new vertex
      else
      {
        double xpos;
        double ypos;
        glfwGetCursorPos (window, &xpos, &ypos);
        std::cout << "Cursor positions are: (" <<  xpos << ", " << ypos << ")\n";
        push_vertex(xpos, ypos, glm::vec4(0.5,0.5,0.5,1.0));
      }
    }
  }
};
