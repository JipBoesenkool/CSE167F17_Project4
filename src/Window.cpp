#include "window.h"
#include <glm/gtx/vector_angle.hpp>
#include <glm/ext.hpp>

const char* window_title = "Roller Coaster";
CubeMapModel* skybox;
Model* frustum;
glm::vec4 Window::frustumPlanes[6];
bool cullCam 		= true;
bool Window::cull 	= true;

double lastFrameTime = 1.0f;
int nbFrames = 0;

Scene *sceneProj3;

GLint shaderProgram;
GLint shaderSkyBoxProgram;
GLint activeShader;

//Lights
DirLightModel *dirLightObj;

// Default camera parameters
Camera Window::camera( glm::vec3(0.0f, 1.0f, 20.0f) );

enum class ModelState
{
	None = 0,
	Rotation,
	Transform,
	Picking
};

ModelState modelState = ModelState::None;
glm::vec3 lastMousePos = glm::vec3(0);
bool firstMouse = true;

int Window::selectedObject = -1;
int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;
glm::mat4 Window::cullV;

bool Window::NDEBUG = false;
GLint Window::shaderEnvProgram;
GLint Window::shaderPickProgram;
GLint Window::shaderLineProgram;
GLint Window::shaderSimpleProgram;
GLint Window::shaderNormalProgram;
GLint Window::shaderPhongProgram;
GLint Window::shaderVisualLightProgram;

void Window::initialize_objects()
{
	Window::shaderEnvProgram = LoadShaders("../resources/shaders/enviroment.vert", "../resources/shaders/enviroment.frag");
	Window::shaderPickProgram = LoadShaders("../resources/shaders/picking.vert", "../resources/shaders/picking.frag");
	Window::shaderLineProgram = LoadShaders("../resources/shaders/line.vert", "../resources/shaders/line.frag");
	Window::shaderSimpleProgram = LoadShaders("../resources/shaders/shader.vert", "../resources/shaders/shader.frag");
	Window::shaderNormalProgram = LoadShaders("../resources/shaders/shaderNormal.vert", "../resources/shaders/shaderNormal.frag");
	Window::shaderPhongProgram = LoadShaders("../resources/shaders/fullPhong.vert", "../resources/shaders/fullPhong.frag");
	Window::shaderVisualLightProgram = LoadShaders("../resources/shaders/lamp.vert", "../resources/shaders/lamp.frag");
	shaderSkyBoxProgram = LoadShaders("../resources/shaders/skyBox.vert", "../resources/shaders/skyBox.frag");
	activeShader = Window::shaderPhongProgram;

	//Skybox
	skybox = new CubeMapModel(shaderSkyBoxProgram, "../resources/textures/skybox", new Transform() );

	//Set up static camera
	glUseProgram(Window::shaderPhongProgram);
	GLint viewPosLoc     = glGetUniformLocation(Window::shaderPhongProgram, "viewPos");
	glUniform3f(viewPosLoc, Window::camera.Position.x, Window::camera.Position.y, Window::camera.Position.z);

	//Light objects
	//Point light
	dirLightObj = new DirLightModel(Window::shaderPhongProgram, new Transform(true, glm::vec3(1.0f)));

	sceneProj3 = new Scene();
	//Setup frustum cube
	frustum = new Model("../resources/models/cube.obj", shaderSimpleProgram, new Transform() );
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	delete(skybox);

	delete(dirLightObj);

	glDeleteProgram(Window::shaderPickProgram);
	glDeleteProgram(Window::shaderLineProgram);
	glDeleteProgram(Window::shaderNormalProgram);
	glDeleteProgram(Window::shaderPhongProgram);
	glDeleteProgram(Window::shaderVisualLightProgram);
	glDeleteProgram(shaderSkyBoxProgram);

	lastFrameTime = glfwGetTime();
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
		P = glm::perspective(Window::camera.Zoom, (float)width / (float)height, 0.1f, 1000.0f);
		V = Window::camera.GetViewMatrix();
	}
}

void Window::idle_callback()
{
	sceneProj3->Update();
}

void Window::display_callback(GLFWwindow* window)
{
	//FPS counter
	CalculateFramesPerSecond(window);

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	P = glm::perspective(Window::camera.Zoom, (float)width / (float)height, 0.1f, 1000.0f);
	V = Window::camera.GetViewMatrix();

	//TODO: set globally for all shaders
	//Update view, projection matrices
	glUseProgram(Window::shaderSimpleProgram);
	GLint uProjection 	= glGetUniformLocation(Window::shaderSimpleProgram, "projection");
	GLint uView 		= glGetUniformLocation(Window::shaderSimpleProgram, "view");
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);

	glUseProgram(Window::shaderEnvProgram);
	uProjection 	= glGetUniformLocation(Window::shaderEnvProgram, "projection");
	uView 		= glGetUniformLocation(Window::shaderEnvProgram, "view");
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);

	glUseProgram(Window::shaderPickProgram);
	uProjection 	= glGetUniformLocation(Window::shaderPickProgram, "projection");
	uView 		= glGetUniformLocation(Window::shaderPickProgram, "view");
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);

	glUseProgram(Window::shaderLineProgram);
	uProjection 	= glGetUniformLocation(Window::shaderLineProgram, "projection");
	uView 		= glGetUniformLocation(Window::shaderLineProgram, "view");
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);

	glUseProgram(Window::shaderPhongProgram);
	uProjection 	= glGetUniformLocation(Window::shaderPhongProgram, "projection");
	uView 		= glGetUniformLocation(Window::shaderPhongProgram, "view");
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);

	// Now send these values to the shader program
	glUseProgram(Window::shaderVisualLightProgram);
	uProjection 	= glGetUniformLocation(Window::shaderVisualLightProgram, "projection");
	uView 		= glGetUniformLocation(Window::shaderVisualLightProgram, "view");
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);

	glUseProgram(Window::shaderNormalProgram);
	uProjection 	= glGetUniformLocation(Window::shaderNormalProgram, "projection");
	uView 		= glGetUniformLocation(Window::shaderNormalProgram, "view");
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);

	glUseProgram(shaderSkyBoxProgram);
	uProjection 	= glGetUniformLocation(shaderSkyBoxProgram, "projection");
	uView 		= glGetUniformLocation(shaderSkyBoxProgram, "view");
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);

	//Draw skybox
	skybox->Draw( glm::mat4(1.0f) );

	// Use coresponding shader when setting uniforms/drawing objects
	glUseProgram(activeShader);
	GLint viewPosLoc     = glGetUniformLocation(activeShader, "viewPos");
	glUniform3f(viewPosLoc, Window::camera.Position.x, Window::camera.Position.y, Window::camera.Position.z);

	glUseProgram(Window::shaderEnvProgram);
	viewPosLoc     		= glGetUniformLocation(Window::shaderEnvProgram, "viewPos");
	glUniform3f(viewPosLoc, Window::camera.Position.x, Window::camera.Position.y, Window::camera.Position.z);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->m_textureID);

	sceneProj3->Draw();


	if(cullCam)
	{
		Window::cullV = Window::V;
		CalculateFrustumPlanes();
	}

	//Debug: draw frustum
	if(NDEBUG)
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		if(cullCam)
		{
			frustum->m_transform->SetPosition( Window::camera.Position);
			frustum->m_transform->m_rotation = glm::vec3( Window::camera.Pitch, -(Window::camera.Yaw + 90.0f), 0.0f);
		}

		glm::mat4 frustumMatrix = frustum->m_transform->GetModelMatrix() * glm::inverse(P);
		frustum->Draw( frustumMatrix );
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glEnable(GL_CULL_FACE);
	}

	//Draw the lights
	dirLightObj->Draw( glm::mat4(1.0f) );

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if(key == GLFW_KEY_S && modelState == ModelState::Picking)
		{
			Window::selectedObject = -1;
			modelState = ModelState::None;
		}
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
		if (key == GLFW_MOUSE_BUTTON_1)
		{
			modelState = ModelState::Picking;
			std::cout<<"picking state"<<std::endl;
		}
		if (key == GLFW_KEY_S)
		{
			modelState = ModelState::Picking;
			std::cout<<"picking state"<<std::endl;
		}
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
			if(activeShader == Window::shaderNormalProgram)
			{
				activeShader = shaderPhongProgram;
			}
			else
			{
				activeShader = Window::shaderNormalProgram;
			}
		}
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_C)
		{
			Window::cull = !Window::cull;
		}
		if (key == GLFW_KEY_V)
		{
			cullCam = !cullCam;
		}
		if (key == GLFW_KEY_B)
		{
			Window::NDEBUG = !Window::NDEBUG;
		}

		//Translation
		if (key == GLFW_KEY_UP)
		{
			Window::camera.ProcessKeyboard( Camera_Movement::FORWARD, 0.1f );
		}
		if (key == GLFW_KEY_DOWN)
		{
			Window::camera.ProcessKeyboard( Camera_Movement::BACKWARD, 0.1f );
		}
		if (key == GLFW_KEY_LEFT)
		{
			Window::camera.ProcessKeyboard( Camera_Movement::LEFT, 0.1f );
		}
		if (key == GLFW_KEY_RIGHT)
		{
			Window::camera.ProcessKeyboard( Camera_Movement::RIGHT, 0.1f );
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
				float sensitivity = 5.0f;
				float rotAngle = velocity * sensitivity;

				Window::camera.ProcessMouseMovement(rotAngle * rotAxis);
			}
		}
		break;
		case ModelState::Transform:
		{
			float xoffset = xpos - lastMousePos.x;
			float yoffset = lastMousePos.y - ypos;

			float sensitivity = 0.05;
			//xoffset *= sensitivity;
			//yoffset *= sensitivity;

			Window::camera.ProcessMouseMovement( xoffset, yoffset, false);
		};
		break;
		case ModelState::Picking:
		{
			//Pick object
			if(selectedObject < 0)
			{
				sceneProj3->MouseSelect( xpos, ypos );
			}
			else
			{
				//move object
				float xoffset = xpos - lastMousePos.x;
				float yoffset = lastMousePos.y - ypos;
				glm::vec4 relMove = glm::vec4(xoffset, yoffset, 0.0f, 0.0f);
				relMove = Window::V * relMove;

				float sensitivity = 0.05;
				relMove *= sensitivity;

				sceneProj3->m_controlPoints[selectedObject]->Move( glm::vec3(relMove.x, relMove.y, -relMove.z) );
			}
		}
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

	Window::camera.ProcessMouseScroll(yoffset);
	P = glm::perspective(Window::camera.Zoom, (float)width / (float)height, 0.1f, 1000.0f);
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

//http://lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final
glm::vec3 Window::AngleBetween(glm::vec3 u, glm::vec3 v)
{
	glm::vec3 w = glm::cross(u, v);
	glm::quat q = glm::quat(glm::dot(u, v), w.x, w.y, w.z);
	q.w += q.length();
	//q = glm::normalize(q);
	return glm::eulerAngles(q);
}

void Window::CalculateFramesPerSecond(GLFWwindow* window)
{
	double currentFrameTime = glfwGetTime();
	nbFrames++;
	if ( currentFrameTime - lastFrameTime >= 1.0f )
	{
		//Information
		std::string str(window_title);
		str += " - " + std::to_string(nbFrames) + "fps";
		std::string cullingBool = (Window::cull) ? "true" : "false";
		str += " - culling: " + cullingBool;

		//Set window title
		glfwSetWindowTitle(window, str.c_str() );
		nbFrames = 0;
		lastFrameTime += 1.0;
	}
}

//http://www.lighthouse3d.com/tutorials/view-frustum-culling/clip-space-approach-extracting-the-planes/
void Window::CalculateFrustumPlanes(  )
{
	// Extracting the planes.
	glm::mat4 matrix = Window::P * Window::cullV;
	glm::vec4 rowX = glm::row(matrix, 0);
	glm::vec4 rowY = glm::row(matrix, 1);
	glm::vec4 rowZ = glm::row(matrix, 2);
	glm::vec4 rowW = glm::row(matrix, 3);

	Window::frustumPlanes[0] = glm::normalize(rowW + rowX);
	Window::frustumPlanes[1] = glm::normalize(rowW - rowX);
	Window::frustumPlanes[2] = glm::normalize(rowW + rowY);
	Window::frustumPlanes[3] = glm::normalize(rowW - rowY);
	Window::frustumPlanes[4] = glm::normalize(rowW + rowZ);
	Window::frustumPlanes[5] = glm::normalize(rowW - rowZ);

	// Normalizing the planes.
	for( int i = 0; i < 6; i++ )
	{
		glm::vec3 normal(Window::frustumPlanes[i].x, Window::frustumPlanes[i].y, Window::frustumPlanes[i].z);
		float length = glm::length(normal);
		Window::frustumPlanes[i] = -Window::frustumPlanes[i] / length;
	}
}
