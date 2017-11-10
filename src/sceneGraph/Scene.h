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

class Scene
{
//Members
private:
	//Main node
	TransformNode world;
//Functions
public:
	Scene();

	virtual void Draw();
	virtual void Update();
};


#endif //SCENE_H
