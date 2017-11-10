//
// Created by Jip Boesenkool on 09/11/2017.
//

#ifndef SCENE_H
#define SCENE_H

//Type of nodes
#include "Node.h"
#include "TransformNode.h"
#include "GeometryNode.h"

#include "../renderer/model/Model.h"
#include "../renderer/lighting/PointLightModel.h"

class Scene
{
//Members
private:
	//Main node
	TransformNode world;
	TransformNode *robot2world;
	TransformNode *head2robot;
	TransformNode *body2robot;
	TransformNode *limb2robot;
	TransformNode *eye2head;
	TransformNode *ant2head;

	TransformNode *bunny2robot;
	TransformNode *light2world;

	PointLightModel *pointLightObj;
//Functions
public:
	Scene();

	virtual void Draw();
	virtual void Update();
};


#endif //SCENE_H
