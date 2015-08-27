#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>  // library that contains file input/output functions

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"


// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

namespace csX75
{
  //! Initialize GL State
  void initGL(void);

  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  //!GLFW mouse callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

};

extern int current_system_state;
extern int num_vertices;
extern glm::vec4 *v_positions;
extern glm::vec4 *v_colors;
void ensureRoomForVertex(void);
void push_vertex(double, double, glm::vec4);
void push_vertex(double, double, double, glm::vec4);

#endif
