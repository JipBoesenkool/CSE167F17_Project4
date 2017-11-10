//
// Created by Jip Boesenkool on 26/10/2017.
//
#include "PointLightModel.h"
#include "../../Window.h"

PointLightModel::PointLightModel(GLuint phongShader, GLuint shader, Transform *transform)
		: Model("../resources/models/sphere.obj", shader, transform)
{
	m_phongShader = phongShader;
	m_shader = shader;
	m_transform = transform;
	m_transform->Scale(0.25f);

	m_pointLight.m_position = m_transform->m_position;
	m_pointLight.m_ambient = glm::vec3(0.2f); // Low influence
	m_pointLight.m_diffuse = glm::vec3(0.5f);
	m_pointLight.m_specular = glm::vec3(1.0f);
	m_pointLight.m_constant    = 1.0f;
	m_pointLight.m_linear      = 0.09f;
	m_pointLight.m_quadratic   = 0.032f;

	//Set up phong shader
	glUseProgram(m_phongShader);
	m_pointLight.SetUniform(m_phongShader);
}

void PointLightModel::Draw( glm::mat4 m )
{
	glUseProgram(m_shader);
	GLint colorLoc     = glGetUniformLocation(m_shader, "color");
	glUniform3f(colorLoc, m_pointLight.m_specular.r, m_pointLight.m_specular.g, m_pointLight.m_specular.b);

	Model::Draw( m );
}

void PointLightModel::Update()
{
	//Update lights etc
	m_pointLight.m_position = m_transform->m_position;

	//update phong shader
	glUseProgram(m_phongShader);
	m_pointLight.SetUniform(m_phongShader);
}
