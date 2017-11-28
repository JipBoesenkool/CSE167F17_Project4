//
// Created by Jip Boesenkool on 27/11/2017.
//

#ifndef CSE167_PROJECT3_CONTROLPOINT_H
#define CSE167_PROJECT3_CONTROLPOINT_H

#include "TransformNode.h"
#include "BezierHandleNode.h"

class ControlPoint : public TransformNode
{
//Members
public:
	BezierHandleNode *parent;
	BezierHandleNode *nextParent;
//Functions
public:
	ControlPoint();
	~ControlPoint();

	void Draw(glm::mat4 C) override;
	void Update() override;
};


#endif //CSE167_PROJECT3_CONTROLPOINT_H
