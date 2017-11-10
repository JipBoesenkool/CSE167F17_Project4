//
// Created by Jip Boesenkool on 26/10/2017.
//
#include "SpotLightModel.h"

SpotLightModel::SpotLightModel(GLuint shader, Transform *transform)
		: Model("../resources/models/cone.obj", shader, transform)
{
	m_shader = shader;
	m_transform = transform;
	transform->Scale(0.25f);
	transform->Rotate( glm::vec3(0.0f,0.0f,-90.0f) );

	m_spotLight.m_position = transform->m_position;
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

void SpotLightModel::Draw( glm::mat4 m )
{
	glUseProgram(m_shader);
	GLint colorLoc     = glGetUniformLocation(m_shader, "color");
	glUniform3f(colorLoc, m_spotLight.m_specular.r, m_spotLight.m_specular.g, m_spotLight.m_specular.b);

	Model::Draw( m );
}

void SpotLightModel::Update()
{
	m_spotLight.m_position = m_transform->m_position;
	m_spotLight.m_direction = glm::normalize( glm::vec3(0.0f) - m_transform->m_position );

	glm::mat4 translation = glm::translate( glm::mat4( 1.0f ), m_spotLight.m_position );
	float angle = glm::dot( glm::vec3( 1.0f, 0.0f, 0.0f ), m_spotLight.m_direction );
	glm::quat direction = glm::angleAxis( acos( angle ), glm::normalize(glm::cross( glm::vec3( 1.0f, 0.0f, 0.0f ), m_spotLight.m_direction )) );
	glm::quat QuatAroundZ = glm::quat( glm::vec3(0.0,0.0,glm::radians(90.0f)) );
	//TODO: broken
	//m_transform->m_position.m_matrix = translation * glm::mat4_cast( (direction * QuatAroundZ) );

	//update phong shader
	glUseProgram(m_shader);
	m_spotLight.SetUniform(m_shader);
}
