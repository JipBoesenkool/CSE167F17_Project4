//
// Created by Jip Boesenkool on 12/11/2017.
//

#include "BoundingSphere.h"
#include "../Window.h"

BoundingSphere::BoundingSphere( Transform *transform )
{
	m_transform = transform;
	m_model = new Model("../resources/models/sphere.obj", Window::shaderSimpleProgram, transform);
	m_radius = 2.0f;
}

void BoundingSphere::Draw( glm::mat4 C )
{
	//Enable point rendering
	if(Window::NDEBUG)
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		m_model->Draw(C);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
}

/*
	glm::mat4 mvp = Window::P * Window::cullV * C;
	glm::vec4 canPos = mvp * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 radius = mvp * glm::vec4(m_radius, m_radius, m_radius, 1.0f);
	canPos = canPos / canPos.w;

	//Culling in canonial-volume space
	if(	canPos.x < 1.0f && canPos.x > -1.0f &&
		canPos.y < 1.0f && canPos.y > -1.0f &&
		canPos.z < 1.0f && canPos.z > -1.0f)
	{
		return true;
	}

	return false;
	 */
bool BoundingSphere::Cull( glm::mat4 C )
{
	glm::vec4 center = C * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	for (glm::vec4 plane : Window::frustumPlanes)
	{
		float distance = plane.x * center.x + plane.y * center.y + plane.z * center.z + plane.w - m_radius;
		if (distance > 0)
		{
			return false;
		}
	}

	return true;
}