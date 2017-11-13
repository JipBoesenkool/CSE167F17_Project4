//
// Created by Jip Boesenkool on 26/10/2017.
//
#include "Transform.h"

//Getters & Setters
glm::mat4 Transform::GetModelMatrix()
{
	if(m_updateMatrix) { UpdateMatrix(); }
	return m_matrix;
}

glm::mat4 Transform::GetPositionMatrix()
{
	glm::mat4 transform(1);
	transform = glm::translate(transform, m_position);
	return transform;
}

glm::mat4 Transform::GetRotationMatrix()
{
	glm::mat4 transform(1);
	transform = glm::rotate(transform, m_rotation.x / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, m_rotation.y / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, m_rotation.z / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	return transform;
}

glm::mat4 Transform::GetScaleMatrix()
{
	glm::mat4 transform(1);
	transform = glm::scale(transform, m_scale);
	return transform;
}

//Public functions
Transform::Transform(bool localOrientation, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	m_position 	= position;
	m_rotation 	= rotation;
	m_scale		= scale;
	m_localOrientation = localOrientation;

	m_updateMatrix = true;
}

void Transform::SetPosition(glm::vec3 position)
{
	m_position = position;
	m_updateMatrix = true;
}

void Transform::Move(glm::vec3 direction)
{
	m_position += direction;
	m_updateMatrix = true;
}

void Transform::Rotate(glm::vec3 rotation)
{
	m_rotation += rotation;
	if (m_rotation.x > 360.0f || m_rotation.x < -360.0f) m_rotation.x = 0.0f;
	if (m_rotation.y > 360.0f || m_rotation.y < -360.0f) m_rotation.y = 0.0f;
	if (m_rotation.z > 360.0f || m_rotation.z < -360.0f) m_rotation.z = 0.0f;
	m_updateMatrix = true;
}

void Transform::Scale(glm::vec3 scale)
{
	m_scale += scale;
	m_updateMatrix = true;
}

void Transform::Scale(float scale)
{
	m_scale *= scale;
	m_updateMatrix = true;
}

void Transform::ResetPosition()
{
	m_position = glm::vec3(0.0f);
	m_updateMatrix = true;
}

void Transform::ResetRotation()
{
	m_rotation = glm::vec3(0.0f);
	m_updateMatrix = true;
}

void Transform::ResetScale()
{
	m_scale = glm::vec3(1.0f);
	m_updateMatrix = true;
}

//Private functions
void Transform::UpdateMatrix()
{
	glm::mat4 T = GetPositionMatrix();
	glm::mat4 R = GetRotationMatrix();
	glm::mat4 S = GetScaleMatrix();

	if(m_localOrientation)
	{
		m_matrix = T * R * S;
	}
	else
	{
		m_matrix = R * T * S;
	}
	m_updateMatrix = false;
}


