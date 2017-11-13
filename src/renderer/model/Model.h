#ifndef MODEL_H
#define MODEL_H

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

class Model
{
//Members
public:
	//Composition, Model has
	Mesh m_mesh;
	Material m_material;
	Transform *m_transform;
	GLint m_shader;

	// These variables are needed for the shader program
	//Opengl
	GLuint m_VBO, m_VAO, m_EBO;

//Functions
public:
	Model();
	Model(const char* filepath, GLuint shader, Transform *transform);
	~Model();

	void SetupMesh();
	virtual void Draw( glm::mat4 m );
	virtual void Update();
};

#endif