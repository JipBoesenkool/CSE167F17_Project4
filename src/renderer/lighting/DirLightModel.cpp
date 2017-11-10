//
// Created by Jip Boesenkool on 26/10/2017.
//
#include "DirLightModel.h"

DirLightModel::DirLightModel(GLuint shader, Transform *transform)
{
	m_shader = shader;
	m_transform = transform;
	m_dirLight.m_direction = glm::normalize( glm::vec3(0.0f) - m_transform->m_position );
	m_dirLight.m_ambient = glm::vec3(0.2f);
	m_dirLight.m_diffuse = glm::vec3(0.5f);
	m_dirLight.m_specular = glm::vec3(1.0f);

	//Set up phong shader
	glUseProgram(shader);
	m_dirLight.SetUniform(shader);
}

void DirLightModel::Draw( glm::mat4 m )
{
	//Empty, nothing to draw
}

void DirLightModel::Update()
{
	//Update lights etc
	m_dirLight.m_direction = glm::normalize( glm::vec3(0.0f) - m_transform->m_position );

	//update phong shader
	glUseProgram(m_shader);
	m_dirLight.SetUniform(m_shader);
}
