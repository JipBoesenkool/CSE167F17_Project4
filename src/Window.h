#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#include <GLFW/glfw3.h>

#include "sceneGraph/Scene.h"

#include "renderer/Camera.h"
#include "renderer/model/Model.h"
#include "renderer/model/Transform.h"
#include "renderer/model/CubeMapModel.h"
#include "renderer/lighting/Light.h"
#include "renderer/shader.h"

#include "renderer/lighting/SpotLightModel.h"
#include "renderer/lighting/PointLightModel.h"
#include "renderer/lighting/DirLightModel.h"

class Window
{
public:
	static GLint shaderNormalProgram;
	static GLint shaderVisualLightProgram;
	static GLint shaderPhongProgram;
	static int width;
	static int height;
	static glm::mat4 P; // P for projection
	static glm::mat4 V; // V for view
	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static glm::vec3 trackBallMapping(double xpos, double ypos);
};

#endif
