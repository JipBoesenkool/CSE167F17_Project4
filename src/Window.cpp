#include "window.h"

const char* window_title = "GLFW Starter Project";
Cube * cube;
Model *bunny;
Model *dragon;
Model *bear;
Model* activeObject;
Model* selectedObject;

//GLint shaderProgram;
GLint shaderNormalProgram;
GLint shaderPhongProgram;
GLint shaderVisualLightProgram;
GLint activeShader;

//Lights
PointLightModel *pointLightObj;
SpotLightModel *spotLightObj;
DirLightModel *dirLightObj;
int selectedLight = 0;

// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, 20.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

enum class ModelState
{
	None = 0,
	Rotation,
	Transform
};

ModelState modelState = ModelState::None;
glm::vec3 lastMousePos = glm::vec3(0);
bool firstMouse = true;

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;

void Window::initialize_objects()
{
	// Load the shader program. Make sure you have the correct filepath up top
	//shaderProgram = LoadShaders("../resources/shaders/shader.vert", "../resources/shaders/shader.frag");
	shaderNormalProgram = LoadShaders("../resources/shaders/shaderNormal.vert", "../resources/shaders/shaderNormal.frag");
	shaderPhongProgram = LoadShaders("../resources/shaders/phong.vert", "../resources/shaders/phong.frag");
	shaderVisualLightProgram = LoadShaders("../resources/shaders/lamp.vert", "../resources/shaders/lamp.frag");
	activeShader = shaderPhongProgram;

	bunny = new Model("../resources/models/bunny.obj");
	//The third object should have significant diffuse and specular reflection components.
	bunny->m_material = Material{
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			76.8f
	};


	//Set up static camera
	glUseProgram(shaderPhongProgram);
	GLint viewPosLoc     = glGetUniformLocation(shaderPhongProgram, "viewPos");
	glUniform3f(viewPosLoc, cam_pos.x, cam_pos.y, cam_pos.z);
	GLint selLightLoc     = glGetUniformLocation(shaderPhongProgram, "selectedLight");
	glUniform1f(selLightLoc, 0.0f);

	//Light objects
	//Point light
	pointLightObj = new PointLightModel(shaderPhongProgram, glm::vec3(-2.0f, 0.0f, 1.0f));
	spotLightObj = new SpotLightModel(shaderPhongProgram, glm::vec3(0.0f, 2.0f, 0.0f));
	dirLightObj = new DirLightModel(shaderPhongProgram, glm::vec3(1.0f));

	glUseProgram(shaderPhongProgram);
	bunny->m_material.SetUniform(shaderPhongProgram);

	activeObject = bunny;
	selectedObject = bunny;
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	delete(bunny);
	delete(dragon);
	delete(bear);

	delete(dirLightObj);
	delete(spotLightObj);
	delete(pointLightObj);

	glDeleteProgram(shaderNormalProgram);
	glDeleteProgram(shaderPhongProgram);
	glDeleteProgram(shaderVisualLightProgram);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
	selectedObject->Update();
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use coresponding shader when setting uniforms/drawing objects
	glUseProgram(activeShader);

	// Use coresponding shader when setting uniforms/drawing objects
	GLint viewPosLoc     = glGetUniformLocation(activeShader, "viewPos");
	glUniform3f(viewPosLoc, cam_pos.x, cam_pos.y, cam_pos.z);
	activeObject->Draw( activeShader );

	//Draw the lights
	activeObject->Draw( shaderVisualLightProgram );
	if(selectedLight == 1 || selectedLight == 0)
	{
		dirLightObj->Draw( shaderVisualLightProgram );
	}
	if(selectedLight == 2 || selectedLight == 0)
	{
		pointLightObj->Draw( shaderVisualLightProgram );
	}
	if(selectedLight == 3 || selectedLight == 0)
	{
		spotLightObj->Draw( shaderVisualLightProgram );
	}

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if(key == GLFW_KEY_LEFT_ALT && modelState == ModelState::Rotation)
		{
			modelState = ModelState::None;
		}
		else if(key == GLFW_KEY_LEFT_CONTROL && modelState == ModelState::Transform)
		{
			modelState = ModelState::None;
		}
	}

	// Check for a key press
	if (action == GLFW_PRESS)
	{
		//mouse input
		if (key == GLFW_KEY_LEFT_ALT)
		{
			modelState = ModelState::Rotation;
			std::cout<<"rotation state"<<std::endl;
		}
		if (key == GLFW_KEY_LEFT_CONTROL)
		{
			std::cout<<"Transform state"<<std::endl;
			modelState = ModelState::Transform;
		}
		if (key == GLFW_KEY_N)
		{
			if(activeShader == shaderNormalProgram)
			{
				activeShader = shaderPhongProgram;
			}
			else
			{
				activeShader = shaderNormalProgram;
			}
		}
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_F1)
		{
			activeObject = bunny;
			bunny->m_material.SetUniform(shaderPhongProgram);
		}
		if (key == GLFW_KEY_F2)
		{
			if(dragon == nullptr)
			{
				dragon = new Model("../resources/models/dragon.obj");
				//Another model should only use diffuse reflection, with zero shininess.
				//Modified red rubber
				dragon->m_material = Material{
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.5f, 0.4f, 0.4f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						0.0f
				};
			}
			activeObject = dragon;
			dragon->m_material.SetUniform(shaderPhongProgram);
		}
		if (key == GLFW_KEY_F3)
		{
			if(bear == nullptr)
			{
				bear = new Model("../resources/models/bear.obj");
				//One of the models should be very shiny, with no diffuse reflection.
				//Modified emerald
				bear->m_material = Material{
						glm::vec3(0.0215f, 0.1745f, 0.0215), 	//amb
						glm::vec3(0.0f),				//dif
						glm::vec3(0.633f, 0.727811f, 0.633f),	//spec
						76.8f
				};
			}
			activeObject = bear;
			bear->m_material.SetUniform(shaderPhongProgram);
		}
		//Reset transform
		if (key == GLFW_KEY_R)
		{
			if(mods == GLFW_MOD_SHIFT)
			{
				selectedObject->m_world.ResetRotation();
				selectedObject->m_world.ResetScale();

				selectedObject->m_local.ResetRotation();
				selectedObject->m_local.ResetScale();
			}
			else
			{
				selectedObject->m_world.ResetPosition();
				selectedObject->m_local.ResetPosition();
			}
		}
		//Toggle selectable object
		if (key == GLFW_KEY_1)
		{
			selectedObject = dirLightObj;
			selectedLight = 1;
			GLint selLightLoc     = glGetUniformLocation(shaderPhongProgram, "selectedLight");
			glUniform1f(selLightLoc, 1.0f);
		}
		if (key == GLFW_KEY_2)
		{
			selectedObject = pointLightObj;
			selectedLight = 2;
			GLint selLightLoc     = glGetUniformLocation(shaderPhongProgram, "selectedLight");
			glUniform1f(selLightLoc, 2.0f);
		}
		if (key == GLFW_KEY_3)
		{
			selectedObject = spotLightObj;
			selectedLight = 3;
			GLint selLightLoc     = glGetUniformLocation(shaderPhongProgram, "selectedLight");
			glUniform1f(selLightLoc, 3.0f);
		}
		if (key == GLFW_KEY_0)
		{
			selectedObject = activeObject;
		}
		if (key == GLFW_KEY_9)
		{
			selectedLight = 0;
			GLint selLightLoc     = glGetUniformLocation(shaderPhongProgram, "selectedLight");
			glUniform1f(selLightLoc, 0.0f);
		}
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		//Translation
		if (key == GLFW_KEY_X)
		{
			if(modelState == ModelState::Transform)
			{
				glm::vec3 dir;
				(mods == 2) ? dir = glm::vec3(1,0,0) : dir = glm::vec3(-1,0,0);
				selectedObject->m_local.Move(dir);
			}
			else if(modelState == ModelState::Rotation)
			{
				glm::vec3 rot;
				(mods == 4) ? rot = glm::vec3(-10.0f,0,0) : rot = glm::vec3(10.0f,0,0);
				selectedObject->m_local.Rotate( rot );
			}
		}
		if (key == GLFW_KEY_Y)
		{
			if(modelState == ModelState::Transform)
			{
				glm::vec3 dir;
				(mods == 2) ? dir = glm::vec3(0,1,0) : dir = glm::vec3(0,-1,0);
				selectedObject->m_local.Move(dir);
			}
			else if(modelState == ModelState::Rotation)
			{
				glm::vec3 rot;
				(mods == 4) ? rot = glm::vec3(0,-1.0f,0) : rot = glm::vec3(0,1.0f,0);
				selectedObject->m_local.Rotate( rot );
			}

		}
		if (key == GLFW_KEY_Z)
		{
			if(modelState == ModelState::Transform)
			{
				glm::vec3 dir;
				(mods == 2) ? dir = glm::vec3(0,0,1) : dir = glm::vec3(0,0,-1);
				selectedObject->m_local.Move(dir);
			}
			else if(modelState == ModelState::Rotation)
			{
				glm::vec3 rot;
				(mods == 4) ? rot =glm::vec3(0,0,10.0f): rot=glm::vec3(0,0,-10.0f);
				selectedObject->m_local.Rotate( rot );
			}
		}
		//Rotation
		if (key == GLFW_KEY_O)
		{
			glm::vec3 rot;
			(mods == 4) ? rot =glm::vec3(0,0,10.0f): rot=glm::vec3(0,0,-10.0f);
			selectedObject->m_world.Rotate( rot );
		}
		//Scale
		if (key == GLFW_KEY_S)
		{
			float scale = 2;
			(mods == GLFW_MOD_SHIFT) ? scale = 2 : scale = 0.5f;
			selectedObject->m_local.Scale(scale);
		}
		//Spotlight
		if (key == GLFW_KEY_W)
		{
			float cutoff;
			(mods == GLFW_MOD_SHIFT) ? cutoff = 1.0f : cutoff = -1.0f;
			if(selectedObject == spotLightObj)
			{
				spotLightObj->m_spotLight.m_cutoff += cutoff;
				spotLightObj->m_spotLight.m_outercutoff += cutoff;
			}
		}
		if (key == GLFW_KEY_E)
		{
			float cutoff;
			(mods == GLFW_MOD_SHIFT) ? cutoff = 1.0f : cutoff = -1.0f;
			if(selectedObject == spotLightObj)
			{
				spotLightObj->m_spotLight.m_outercutoff += cutoff;
				if(spotLightObj->m_spotLight.m_outercutoff < spotLightObj->m_spotLight.m_cutoff)
				{
					spotLightObj->m_spotLight.m_outercutoff = spotLightObj->m_spotLight.m_cutoff;
				}
			}
		}
	}
}

void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastMousePos.x = xpos;
		lastMousePos.y = ypos;
		firstMouse = false;
		return;
	}

	switch(modelState)
	{
		case ModelState::Rotation:
		{
			// Map the mouse position to a logical sphere location.
			glm::vec3 curPoint = trackBallMapping( xpos, ypos );
			//std::cout<<"current:"<<curPoint.x<<", "<<curPoint.y<<", "<<curPoint.z<<std::endl;
			// Map the mouse position to a logical sphere location.
			glm::vec3 lastPoint = trackBallMapping( lastMousePos.x, lastMousePos.y );
			//std::cout<<"last:"<<lastPoint.x<<", "<<lastPoint.y<<", "<<lastPoint.z<<std::endl;
			glm::vec3 direction = curPoint - lastPoint;
			//std::cout<<"dir:"<<direction.x<<", "<<direction.y<<", "<<direction.z<<std::endl;
			float velocity = direction.length();
			if( velocity > 0.0001 ) // If little movement - do nothing.
			{
				// Rotate about the axis that is perpendicular to the great circle connecting the mouse movements.
				glm::vec3 rotAxis = glm::cross( lastPoint, curPoint );
				float sensitivity = 1.0f;
				float rotAngle = velocity * sensitivity;
				//activeObject->m_world.Rotate(rotAngle * rotAxis);
				selectedObject->m_world.m_matrix = selectedObject->m_world.m_matrix * glm::rotate(glm::mat4(1.0f), rotAngle / 180.0f * glm::pi<float>(), rotAxis);
			}
		}
		break;
		case ModelState::Transform:
		{
			float xoffset = xpos - lastMousePos.x;
			float yoffset = lastMousePos.y - ypos;

			float sensitivity = 0.05;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			selectedObject->m_local.Move( glm::vec3(xoffset, yoffset, 0) );
		};
		break;
	}
	// Save the location of the current point for the next movement.
	lastMousePos.x = xpos;
	lastMousePos.y = ypos;
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(modelState == ModelState::Transform)
	{
		float sensitivity = 0.05;
		yoffset *= sensitivity;
		selectedObject->m_local.Move( glm::vec3(0, 0, -yoffset) );
	}
}

glm::vec3 Window::trackBallMapping(double xpos, double ypos)
{
	glm::vec3 v = glm::vec3(
			(2.0*xpos - Window::width/2) / Window::width/2,
			(Window::height/2 - 2.0*ypos) / Window::height/2,
			0.0f
	);
	float d = v.length();
	d = (d<1.0) ? d : 1.0;
	v.z = sqrtf(1.001 - d*d);
	v = glm::normalize(v); // Still need to normalize, since we only capped d, not v.
	return v;
}
