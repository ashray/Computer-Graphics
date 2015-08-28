/*
  CS675: Assignment 1

  Model #1: Table

  Referenced from Tutorial 2 colorcube.cpp

  Akshat Kadam - 111030006
*/

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "gl_framework.hpp"
#include "shader_util.hpp"

GLuint shaderProgram;
GLuint vbo, vao;

//-----------------------------------------------------------------

// Table model
//5 cuboids, 6 faces/cuboid, 1 quadrilateral/face, 4 vertices/quadrilateral
const int num_vertices = 120;

//Eight vertices in homogenous coordinates
glm::vec4 positions[8] = {
  // These vertices form the top of the table.
  // Legs will be formed by transforming the top.
  glm::vec4(-0.75, -0.75, 0.1, 1.0),
  glm::vec4(-0.75, 0.75, 0.1, 1.0),
  glm::vec4(0.75, 0.75, 0.1, 1.0),
  glm::vec4(0.75, -0.75, 0.1, 1.0),
  glm::vec4(-0.75, -0.75, 0.0, 1.0),
  glm::vec4(-0.75, 0.75, 0.0, 1.0),
  glm::vec4(0.75, 0.75, 0.0, 1.0),
  glm::vec4(0.75, -0.75, 0.0, 1.0)
};

//RGBA colors
glm::vec4 colors[8] = {
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0)
};

int tri_idx=0;
glm::vec4 v_positions[num_vertices];
glm::vec4 v_colors[num_vertices];

glm::vec4 fin_pos[8];
glm::mat4 v_translate;
glm::mat4 v_scale;


// Generates a quad for each face, transforms it and assigns colors to the vertices
void transforme(float tx, float ty, float tz, float sx, float sy, float sz, int a, int b, int c, int d)
{
  v_translate = glm::translate(tx,ty,tz);
  v_scale = glm::scale(sx,sy,sz);

  fin_pos = v_translate*v_scale*positions;

  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = fin_pos[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_positions[tri_idx] = fin_pos[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = fin_pos[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_positions[tri_idx] = fin_pos[d]; tri_idx++;
}

// generate 12 triangles: 36 vertices and 36 colors
void colortable(void)
{
	// Construct the top
	transforme(0.0,0.0,0.0,1.0,1.0,1.0,1,0,3,2);
	transforme(0.0,0.0,0.0,1.0,1.0,1.0,2,3,7,6);
	transforme(0.0,0.0,0.0,1.0,1.0,1.0,3,0,4,7);
	transforme(0.0,0.0,0.0,1.0,1.0,1.0,6,5,1,2);
	transforme(0.0,0.0,0.0,1.0,1.0,1.0,4,5,6,7);
	transforme(0.0,0.0,0.0,1.0,1.0,1.0,5,4,0,1);
	// Top-left leg
	transforme(-0.5,0.5,-0.3,0.33,0.33,3.0,1,0,3,2);
	transforme(-0.5,0.5,-0.3,0.33,0.33,3.0,2,3,7,6);
	transforme(-0.5,0.5,-0.3,0.33,0.33,3.0,3,0,4,7);
	transforme(-0.5,0.5,-0.3,0.33,0.33,3.0,6,5,1,2);
	transforme(-0.5,0.5,-0.3,0.33,0.33,3.0,4,5,6,7);
	transforme(-0.5,0.5,-0.3,0.33,0.33,3.0,5,4,0,1);
	// Top-right leg
	transforme(0.5,0.5,-0.3,0.33,0.33,3.0,1,0,3,2);
	transforme(0.5,0.5,-0.3,0.33,0.33,3.0,2,3,7,6);
	transforme(0.5,0.5,-0.3,0.33,0.33,3.0,3,0,4,7);
	transforme(0.5,0.5,-0.3,0.33,0.33,3.0,6,5,1,2);
	transforme(0.5,0.5,-0.3,0.33,0.33,3.0,4,5,6,7);
	transforme(0.5,0.5,-0.3,0.33,0.33,3.0,5,4,0,1);
	// Bottom-left leg
	transforme(-0.5,-0.5,-0.3,0.33,0.33,3.0,1,0,3,2);
	transforme(-0.5,-0.5,-0.3,0.33,0.33,3.0,2,3,7,6);
	transforme(-0.5,-0.5,-0.3,0.33,0.33,3.0,3,0,4,7);
	transforme(-0.5,-0.5,-0.3,0.33,0.33,3.0,6,5,1,2);
	transforme(-0.5,-0.5,-0.3,0.33,0.33,3.0,4,5,6,7);
	transforme(-0.5,-0.5,-0.3,0.33,0.33,3.0,5,4,0,1);
	// Bottom-right leg
	transforme(0.5,-0.5,-0.3,0.33,0.33,3.0,1,0,3,2);
	transforme(0.5,-0.5,-0.3,0.33,0.33,3.0,2,3,7,6);
	transforme(0.5,-0.5,-0.3,0.33,0.33,3.0,3,0,4,7);
	transforme(0.5,-0.5,-0.3,0.33,0.33,3.0,6,5,1,2);
	transforme(0.5,-0.5,-0.3,0.33,0.33,3.0,4,5,6,7);
	transforme(0.5,-0.5,-0.3,0.33,0.33,3.0,5,4,0,1);
}
//-----------------------------------------------------------------

void initBuffersGL(void)
{
  colortable();

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
  std::string vertex_shader_file("02_vshader.glsl");
  std::string fragment_shader_file("02_fshader.glsl");

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
  glDrawArrays(GL_QUADS, 0, num_vertices);

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
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 2: Colorcube", NULL, NULL);
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

//-------------------------------------------------------------------------
