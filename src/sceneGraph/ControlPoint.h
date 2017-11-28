//
// Created by Jip Boesenkool on 27/11/2017.
//

#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include "TransformNode.h"
#include "BezierHandleNode.h"
#include "GeometryNode.h"

class ControlPoint : public TransformNode
{
//Members
public:
	glm::mat4 m_storedMatrix = glm::mat4(1.0f);
	GeometryNode *m_geoNode;
	ControlPoint *m_cpPaired = nullptr;

	BezierHandleNode *m_parent;
//Functions
public:
	ControlPoint( GeometryNode *geoNode );
	~ControlPoint();

	void Draw(glm::mat4 C) override;
	void Update() override;

	void Move( glm::vec3 dir );
};


#endif //CONTROLPOINT_H
