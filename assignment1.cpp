/*
  CS675: Assignment1

  A program which opens a window and draws the "color cube."

  Modified from An Introduction to OpenGL Programming,
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  And sample code provided by Prof. Parag Chaudhary
  Computer Graphics course, CS 675, Autumn 2015

  Written by Ashray Malhotra
*/

#include "assignment1.hpp"
// #include <glfw3.h>



GLuint shaderProgram;
GLuint vbo, vao;

//-----------------------------------------------------------------

// Let us say our object does not consist of more than 20 points
int num_vertices =20;
glm::vec4 *v_positions = new glm::vec4[num_vertices];
glm::vec4 *v_colors = new glm::vec4[num_vertices];

void initializePositions(void)
{
  // Initialize all the vertex positions to zero
  for (int i=0; i<num_vertices; i++)
  {
    v_positions[i] = glm::vec4(0.0,0.0,0.0,1.0);
  }

  // Setting the default color to white
  for (int i=0; i<num_vertices; i++)
  {
    v_colors[i] = glm::vec4(1.0,1.0,1.0,1.0);
  }

}
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Program Architecture -
// Since we need the ability to be able to add points to the
// screen, this is not a Typical Graphics problem since we don't
// have the model already. We have multiple choices now on how to
// pass data to the graphics pipeline(when to handover data to GPUs)
// The approach we are taking here is that we are passing all the
// vertices again to the GPU once we add a new point, this makes
// managing variables simpler in the GPU side and also for the size
// of the models that we plan to deal with, will not affect the
// performance of the system.
//-----------------------------------------------------------------

void initBuffersGL(void)
{
  initializePositions();
  //Ask GL for a Vertex Attribute Object (vao)
  glGenVertexArrays (1, &vao);
  //Set it as the current array to be used by binding it
  glBindVertexArray (vao);

  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (1, &vbo);

  //Set it as the current buffer to be used by binding it
  glBindBuffer (GL_ARRAY_BUFFER, vbo);

  //Copy the points into the current buffer
  glBufferData (GL_ARRAY_BUFFER, sizeof (v_positions) + sizeof(v_colors), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(v_positions), v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(v_positions), sizeof(v_colors), v_colors );

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("vshader_assignment1.glsl");
  std::string fragment_shader_file("fshader_assignment1.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // set up vertex arrays
  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(v_positions)) );
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw
  glDrawArrays(GL_TRIANGLE_STRIP , 0, num_vertices);

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "Modelling Viewing pipeline", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }

  //! Make the window's context current
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {

      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);

      // Poll for and process events
      glfwPollEvents();
    }

  glfwTerminate();
  return 0;
}

// ---------Remember to delete the manually allocated variables--------
// delete[] v_positions;
// delete[] v_colors;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
