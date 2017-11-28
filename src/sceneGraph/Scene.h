//
// Created by Jip Boesenkool on 09/11/2017.
//

#ifndef SCENE_H
#define SCENE_H

//Type of nodes
#include "Node.h"
#include "TransformNode.h"
#include "GeometryNode.h"
#include "BezierHandleNode.h"

#include "../physics/BoundingVolume.h"
#include "../physics/BoundingSphere.h"

#include "../renderer/model/Model.h"
#include "../renderer/lighting/PointLightModel.h"

class Scene
{
//Members
private:
	//Shaders

	//Main node
	TransformNode world;
	TransformNode *track;
	GeometryNode *redSphere;
	GeometryNode *blueSphere;

	GeometryNode *cart;

	TransformNode *light2world;
	PointLightModel *pointLightObj;
	bool sceneLoaded = false;
//Functions
public:
	Scene();
	~Scene();

	virtual void Draw();
	virtual void Update();
};


#endif //SCENE_H
