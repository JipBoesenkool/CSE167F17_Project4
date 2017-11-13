//
// Created by Jip Boesenkool on 12/11/2017.
//
#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include "BoundingVolume.h"

class BoundingSphere : public BoundingVolume
{
//Members
public:
	float m_radius;
//Functions
public:
	BoundingSphere( Transform *transform );

	void Draw( glm::mat4 C ) override;
	bool Cull( glm::mat4 m ) override;
};

#endif //BOUNDINGSPHERE_H
