//
// Created by Jip Boesenkool on 26/10/2017.
//
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vertex.h"

class Mesh
{
//Members
public:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	glm::mat4 origin = glm::mat4(1.0f);
//Static
public:
	static Mesh ParseObj(const char* filepath);
//Functions
public:
	Mesh(){};

	void Normalize();
};


#endif //MESH_H
