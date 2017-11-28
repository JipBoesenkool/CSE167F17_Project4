#include "Model.h"
#include "../../Window.h"


Model::Model()
{
	//Empty constructor
}

Model::Model(const char *filepath, GLuint shader, Transform *transform)
{
	m_shader = shader;
	m_transform = transform;
	m_mesh = Mesh::ParseObj(filepath);
	SetupMesh();
}

Model::~Model()
{
	// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a
	// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void Model::SetupMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_mesh.m_vertices.size() * sizeof(Vertex), m_mesh.m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh.m_indices.size() * sizeof(GLuint), m_mesh.m_indices.data(), GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)0);

	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)offsetof(Vertex, m_normal));

	// Vertex texCoords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)offsetof(Vertex, m_texCoords));

	glBindVertexArray(0);
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void Model::Draw( glm::mat4 m )
{
	glUseProgram(m_shader);
	GLint uModel 		= glGetUniformLocation(m_shader, "model");
	glUniformMatrix4fv(uModel, 1, GL_FALSE, &m[0][0]);
	m_material.SetUniform(m_shader);

	// Now Draw the cube. We simply need to bind the VAO associated with it.
	glBindVertexArray(m_VAO);
	// Tell OpenGL to Draw with triangles, using 36 indices, the type of the indices, and the offset to start from
	glDrawElements(GL_TRIANGLES, m_mesh.m_indices.size(), GL_UNSIGNED_INT, 0);
	// Unbind the VAO when we're done so we don't accidentally Draw extra stuff or tamper with its bound buffers
	glBindVertexArray(0);
}

void Model::Update()
{
	//Automatic rotation
	//glm::vec3 rotation = glm::vec3(0, 1.0f, 0);
	//m_local.Rotate(rotation);
}