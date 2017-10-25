#ifndef _MAIN_H_
#define _MAIN_H_

#include <GL/glew.h>
#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/gl3ext.h>
#else
#include <OpenGL/gl3.h>
#endif
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Window.h"

#endif