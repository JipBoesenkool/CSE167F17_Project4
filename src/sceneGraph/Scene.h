//
// Created by Jip Boesenkool on 09/11/2017.
//

#ifndef SCENE_H
#define SCENE_H

//Type of nodes
#include "Node.h"
#include "TransformNode.h"
#include "GeometryNode.h"

#include "../physics/BoundingVolume.h"
#include "../physics/BoundingSphere.h"

#include "../renderer/model/Model.h"
#include "../renderer/lighting/PointLightModel.h"

class Scene
{
//Members
private:
	//Main node
	TransformNode world;
	TransformNode *bullets2world = nullptr;

	TransformNode *robot2world;
	GeometryNode *robot;

	TransformNode *floor2world;
	TransformNode *head2robot;
	TransformNode *body2robot;
	TransformNode *limb2robot;
	TransformNode *eye2head;
	TransformNode *ant2head;

	TransformNode *bunny2robot;
	TransformNode *light2world;

	PointLightModel *pointLightObj;
	bool sceneLoaded = false;
//Functions
public:
	Scene();
	~Scene();

	virtual void Draw();
	virtual void Update();


	void Fire();
};


#endif //SCENE_H
