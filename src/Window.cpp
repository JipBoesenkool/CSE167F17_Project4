#include "window.h"

const char* window_title = "GLFW Starter Project";
Cube * cube;
OBJObject *bunny;
OBJObject *dragon;
OBJObject *bear;
OBJObject* activeObject;

GLint shaderProgram;
GLint shaderNormalProgram;
GLint shaderPhongProgram;
GLint shaderVisualLightProgram;
GLint shaderPointLightProgram;
GLint shaderDirLightProgram;
GLint activeShader;

//Lights
DirLight    dirLight;
OBJObject *dirLightObj;

//pointLights
PointLight pointLights[4];
OBJObject *pointLightObj;

// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, 20.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

enum class MouseState
{
	None = 0,
	Rotation,
	Transform
};

MouseState mouseState = MouseState::None;

glm::vec3 lastMousePos = glm::vec3(0);
bool firstMouse = true;
bool ctrlWasClicked = false;
bool leftWasClicked = false;

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;

void Window::initialize_objects()
{
	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders("../resources/shaders/shader.vert", "../resources/shaders/shader.frag");
	shaderNormalProgram = LoadShaders("../resources/shaders/shaderNormal.vert", "../resources/shaders/shaderNormal.frag");
	shaderPhongProgram = LoadShaders("../resources/shaders/lighting.vert", "../resources/shaders/lighting.frag");

	shaderDirLightProgram = LoadShaders("../resources/shaders/materialColors.vert", "../resources/shaders/dirLight.frag");
	shaderVisualLightProgram = LoadShaders("../resources/shaders/lamp.vert", "../resources/shaders/lamp.frag");
	activeShader = shaderDirLightProgram;

	//dirLightObj = new OBJObject("../resources/models/cone.obj");
	bunny = new OBJObject("../resources/models/bunny.obj");
	// Set material properties
	bunny->m_material = Material{
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			76.8f
	};

	cube = new Cube();

	//Set up lights
	glUseProgram(shaderDirLightProgram);
	dirLight.m_direction = glm::vec3(-0.5f, -1.0f, -0.5f);
	dirLight.m_ambient = glm::vec3(0.2f);
	dirLight.m_diffuse = glm::vec3(0.5f);
	dirLight.m_specular = glm::vec3(1.0f);
	dirLight.SetUniform(shaderDirLightProgram);
	bunny->m_material.SetUniform(shaderDirLightProgram);

	/*
	// Positions of the point lights
	pointLights[0].m_position = glm::vec3( 0.7f,  0.2f,  1.0f);
	pointLights[1].m_position = glm::vec3( 2.3f, -3.3f, -4.0f);
	pointLights[2].m_position = glm::vec3(-4.0f,  2.0f, -12.0f);
	pointLights[3].m_position = glm::vec3( 0.0f,  0.0f, -3.0f);
	glUseProgram(shaderPhongProgram);

	for(int i = 0; i < 4; i++)
	{
		pointLights[i].m_ambient = glm::vec3(0.2f); // Low influence
		pointLights[i].m_diffuse = glm::vec3(0.5f);
		pointLights[i].m_specular = glm::vec3(1.0f);

		pointLights[i].m_constant    = 1.0f;
		pointLights[i].m_linear      = 0.09f;
		pointLights[i].m_quadratic   = 0.032f;

		// Point light
		std::string number = std::to_string(i);
		glUniform3f(glGetUniformLocation(shaderPhongProgram, ("pointLights[" + number + "].position").c_str()), pointLights[i].m_position.x, pointLights[i].m_position.y, pointLights[i].m_position.z);

		glUniform3f(glGetUniformLocation(shaderPhongProgram, ("pointLights[" + number + "].ambient").c_str()), pointLights[i].m_ambient.x, pointLights[i].m_ambient.y, pointLights[i].m_ambient.z);
		glUniform3f(glGetUniformLocation(shaderPhongProgram, ("pointLights[" + number + "].diffuse").c_str()), pointLights[i].m_diffuse.x, pointLights[i].m_diffuse.y, pointLights[i].m_diffuse.z);
		glUniform3f(glGetUniformLocation(shaderPhongProgram, ("pointLights[" + number + "].specular").c_str()), pointLights[i].m_specular.x, pointLights[i].m_specular.y, pointLights[i].m_specular.z);

		glUniform1f(glGetUniformLocation(shaderPhongProgram, ("pointLights[" + number + "].constant").c_str()), pointLights[i].m_constant);
		glUniform1f(glGetUniformLocation(shaderPhongProgram, ("pointLights[" + number + "].linear").c_str()), pointLights[i].m_linear);
		glUniform1f(glGetUniformLocation(shaderPhongProgram, ("pointLights[" + number + "].quadratic").c_str()), pointLights[i].m_quadratic);
	}
	 */

	//dragon.parse("../resources/models/dragon.obj");
	//bear.parse("../resources/models/bear.obj");

	activeObject = bunny;
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	delete(cube);
	delete(bunny);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderNormalProgram);
	glDeleteProgram(shaderPhongProgram);
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

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	// Call the update function the cube
	//cube->update();
	activeObject->update();
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader of programID
	//glUseProgram(shaderProgram);
	// Render the cube
	//cube->draw(shaderProgram);

	glUseProgram(shaderDirLightProgram);
	// Use coresponding shader when setting uniforms/drawing objects
	GLint viewPosLoc     = glGetUniformLocation(shaderDirLightProgram, "viewPos");
	glUniform3f(viewPosLoc, cam_pos.x, cam_pos.y, cam_pos.z);

	glUseProgram(activeShader);
	activeObject->draw(activeShader);

	//Draw the lights
	glUseProgram(shaderVisualLightProgram);
	//dirLightObj->draw(shaderVisualLightProgram);


	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if(key == GLFW_KEY_LEFT_ALT && mouseState == MouseState::Rotation)
		{
			mouseState = MouseState::None;
		}
		else if(key == GLFW_KEY_LEFT_CONTROL && mouseState == MouseState::Transform)
		{
			mouseState = MouseState::None;
		}
	}

	// Check for a key press
	if (action == GLFW_PRESS)
	{
		//mouse input
		if (key == GLFW_KEY_LEFT_ALT)
		{
			mouseState = MouseState::Rotation;
			std::cout<<"rotation state"<<std::endl;
		}
		if (key == GLFW_KEY_LEFT_CONTROL)
		{
			std::cout<<"Transform state"<<std::endl;
			mouseState = MouseState::Transform;
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
		}
		if (key == GLFW_KEY_F2)
		{
			if(dragon == nullptr)
			{
				dragon = new OBJObject("../resources/models/dragon.obj");
			}
			activeObject = dragon;
		}
		if (key == GLFW_KEY_F3)
		{
			if(bear == nullptr)
			{
				bear = new OBJObject("../resources/models/bear.obj");
			}
			activeObject = bear;
		}
		//Reset transform
		if (key == GLFW_KEY_R)
		{
			if(mods == GLFW_MOD_SHIFT)
			{
				activeObject->resetRotation();
				activeObject->resetScale();
			}
			else
			{
				activeObject->resetPosition();
			}
		}
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		//Translation
		if (key == GLFW_KEY_X)
		{
			if(mouseState == MouseState::Transform)
			{
				glm::vec3 dir;
				(mods == 2) ? dir = glm::vec3(1,0,0) : dir = glm::vec3(-1,0,0);
				activeObject->move(dir);
			}
			else if(mouseState == MouseState::Rotation)
			{
				glm::vec3 rot;
				(mods == 4) ? rot = glm::vec3(-10.0f,0,0) : rot = glm::vec3(10.0f,0,0);
				activeObject->rotate( rot );
			}
		}
		if (key == GLFW_KEY_Y)
		{
			if(mouseState == MouseState::Transform)
			{
				glm::vec3 dir;
				(mods == 2) ? dir = glm::vec3(0,1,0) : dir = glm::vec3(0,-1,0);
				activeObject->move(dir);
			}
			else if(mouseState == MouseState::Rotation)
			{
				glm::vec3 rot;
				(mods == 4) ? rot = glm::vec3(0,-1.0f,0) : rot = glm::vec3(0,1.0f,0);
				activeObject->rotate( rot );
			}

		}
		if (key == GLFW_KEY_Z)
		{
			if(mouseState == MouseState::Transform)
			{
				glm::vec3 dir;
				(mods == 2) ? dir = glm::vec3(0,0,1) : dir = glm::vec3(0,0,-1);
				activeObject->move(dir);
			}
			else if(mouseState == MouseState::Rotation)
			{
				glm::vec3 rot;
				(mods == 4) ? rot =glm::vec3(0,0,10.0f): rot=glm::vec3(0,0,-10.0f);
				activeObject->rotate( rot );
			}
		}
		//Rotation
		if (key == GLFW_KEY_O)
		{
			float deg;
			(mods == GLFW_MOD_SHIFT) ? deg=-10.0f : deg=10.0f;
			activeObject->manualRotation(deg);
		}
		//Scale
		if (key == GLFW_KEY_S)
		{
			bool scaleUp;
			(mods == GLFW_MOD_SHIFT) ? scaleUp = true : scaleUp = false;
			activeObject->scaleObject(scaleUp);
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

	switch(mouseState)
	{
		case MouseState::Rotation:
		{
			glm::vec3 curPoint = trackBallMapping( xpos, ypos ); // Map the mouse position to a logical sphere location.
			glm::vec3 lastPoint = trackBallMapping( lastMousePos.x, lastMousePos.y ); // Map the mouse position to a logical sphere location.
			glm::vec3 direction = curPoint - lastPoint;
			float velocity = direction.length();
			if( velocity > 0.0001 ) // If little movement - do nothing.
			{
				// Rotate about the axis that is perpendicular to the great circle connecting the mouse movements.
				glm::vec3 rotAxis = glm::cross( lastPoint, curPoint );
				float sensitivity = 90.0f;
				float rotAngle = velocity * sensitivity;
				//TODO: apply rot matrix last
				//std::cout<<rotAxis.x<<", "<<rotAxis.y<<", "<<rotAxis.z<<std::endl;
				activeObject->rotate( rotAxis * rotAngle );
			}
		}
		break;
		case MouseState::Transform:
		{
			float xoffset = xpos - lastMousePos.x;
			float yoffset = lastMousePos.y - ypos;

			float sensitivity = 0.05;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			activeObject->move( glm::vec3(xoffset, yoffset, 0) );
		};
		break;
	}
	// Save the location of the current point for the next movement.
	lastMousePos.x = xpos;
	lastMousePos.y = ypos;
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	float sensitivity = 0.05;
	yoffset *= sensitivity;
	activeObject->move( glm::vec3(0, 0, -yoffset) );
}

glm::vec3 Window::trackBallMapping(double xpos, double ypos)
{
	glm::vec3 v = glm::vec3(
			(2.0*xpos - Window::width) / Window::width,
			(Window::height - 2.0*ypos) / Window::height,
			0.0
	);
	float d = v.length();
	d = (d<1.0) ? d : 1.0;
	v.z = sqrtf(1.001 - d*d);
	v = glm::normalize(v); // Still need to normalize, since we only capped d, not v.
	return v;
}
