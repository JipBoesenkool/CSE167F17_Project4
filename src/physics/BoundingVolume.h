//
// Created by Jip Boesenkool on 12/11/2017.
//
#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif

#include "../renderer/model/Transform.h"
#include "../renderer/model/Model.h"

class BoundingVolume
{
//Members
public:
	Model *m_model;
	Transform *m_transform;
//Functions
public:
	//base constructor for model?

	virtual void Draw( glm::mat4 m ) = 0;
	virtual bool Cull( glm::mat4 m ) = 0;
	//virtual void Intersects( glm::mat4 m );
};

#endif //BOUNDINGVOLUME_H
