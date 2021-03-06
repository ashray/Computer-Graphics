/*
  A program which opens a window and draws the "color cube."

  Modified from An Introduction to OpenGL Programming,
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by Parag Chaudhuri, 2015
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127
#define GLFW_KEY_M 77

// Dimensions of the window
#define WIDTH 512
#define HEIGHT 512

//Include Files
#include "gl_framework.hpp"
#include "shader_util.hpp"

int current_system_state = 2;

#endif
