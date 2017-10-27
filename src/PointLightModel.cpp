//
// Created by Jip Boesenkool on 26/10/2017.
//
#include "PointLightModel.h"

PointLightModel::PointLightModel(GLuint shader, glm::vec3 position)
		: Model("../resources/models/sphere.obj")
{
	m_shader = shader;
	m_local.m_position = position;
	m_local.Scale(0.25f);

	m_pointLight.m_position = m_local.m_position;
	m_pointLight.m_ambient = glm::vec3(0.2f); // Low influence
	m_pointLight.m_diffuse = glm::vec3(0.5f);
	m_pointLight.m_specular = glm::vec3(1.0f);
	m_pointLight.m_constant    = 1.0f;
	m_pointLight.m_linear      = 0.09f;
	m_pointLight.m_quadratic   = 0.032f;

	//Set up phong shader
	glUseProgram(shader);
	m_pointLight.SetUniform(shader);
}

void PointLightModel::Draw( GLuint shader )
{
	glUseProgram(shader);
	GLint colorLoc     = glGetUniformLocation(shader, "color");
	glUniform3f(colorLoc, m_pointLight.m_specular.r, m_pointLight.m_specular.g, m_pointLight.m_specular.b);

	Model::Draw(shader);
}

void PointLightModel::Update()
{
	//Update lights etc
	m_pointLight.m_position = m_local.m_position;

	//update phong shader
	glUseProgram(m_shader);
	m_pointLight.SetUniform(m_shader);
}
