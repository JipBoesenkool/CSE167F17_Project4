//
// Created by Jip Boesenkool on 21/10/2017.
//

#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_texCoords;
};

#endif //VERTEX_H
