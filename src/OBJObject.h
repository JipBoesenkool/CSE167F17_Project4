#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#include "Vertex.h"
#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Material.h"

class OBJObject
{
//Members
public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> indices;
	std::vector<Vertex> mesh;
	glm::mat4 toWorld;
	glm::mat4 origin;
	glm::vec3 rotation;
	Material m_material;
private:
	glm::vec3 position;
	glm::vec3 originPosition;
	glm::vec3 centerPosition;
	float scale = 1;
	float originScale = 1;

	// These variables are needed for the shader program
	GLuint VBO, VAO, EBO;
	GLuint uProjection, uModelview;

//Functions
public:
	OBJObject();
	OBJObject(const char* filepath);
	~OBJObject();

	void parse(const char* filepath);
	void SetupMesh();
	void draw(GLuint shader);
	void update();

	void move(glm::vec3 direction);
	void rotate(glm::vec3 rotation);
	void manualRotation(float deg);
	void automaticRotation();
	void scaleObject(bool scaleUp);

	void resetPosition();
	void resetRotation();
	void resetScale();
private:
	void calibratePosition();
	void calibrateScale();
};

#endif