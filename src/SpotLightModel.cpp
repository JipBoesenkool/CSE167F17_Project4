//
// Created by Jip Boesenkool on 26/10/2017.
//
#include "SpotLightModel.h"

SpotLightModel::SpotLightModel(GLuint shader, glm::vec3 position)
		: Model("../resources/models/cone.obj")
{
	m_shader = shader;
	m_local.m_position = position;
	m_local.Scale(0.25f);
	//m_local.Rotate( glm::vec3(0.0f,0.0f,-90.0f) );

	m_spotLight.m_position = m_local.m_position;
	m_spotLight.m_direction = glm::normalize( glm::vec3(0.0f) - m_spotLight.m_position );
	m_spotLight.m_ambient = glm::vec3(0.1f); // Low influence
	m_spotLight.m_diffuse = glm::vec3(0.8f);
	m_spotLight.m_specular = glm::vec3(1.0f);
	m_spotLight.m_constant    = 1.0f;
	m_spotLight.m_linear      = 0.007f;
	m_spotLight.m_quadratic   = 0.0002f;
	m_spotLight.m_cutoff = 12.5f;
	m_spotLight.m_outercutoff = 17.5f;

	//Set up phong shader
	glUseProgram(shader);
	m_spotLight.SetUniform(shader);
}

void SpotLightModel::Draw( GLuint shader )
{
	glUseProgram(shader);
	GLint colorLoc     = glGetUniformLocation(shader, "color");
	glUniform3f(colorLoc, m_spotLight.m_specular.r, m_spotLight.m_specular.g, m_spotLight.m_specular.b);

	Model::Draw(shader);
}

void SpotLightModel::Update()
{
	m_spotLight.m_position = m_local.m_position;
	m_spotLight.m_direction = glm::normalize( glm::vec3(0.0f) - m_local.m_position );

	glm::mat4 translation = glm::translate( glm::mat4( 1.0f ), m_spotLight.m_position );
	float angle = glm::dot( glm::vec3( 1.0f, 0.0f, 0.0f ), m_spotLight.m_direction );
	glm::quat direction = glm::angleAxis( acos( angle ), glm::normalize(glm::cross( glm::vec3( 1.0f, 0.0f, 0.0f ), m_spotLight.m_direction )) );
	glm::quat QuatAroundZ = glm::quat( glm::vec3(0.0,0.0,glm::radians(90.0f)) );
	m_world.m_matrix = translation * glm::mat4_cast( (direction * QuatAroundZ) );

	//update phong shader
	glUseProgram(m_shader);
	m_spotLight.SetUniform(m_shader);
}
