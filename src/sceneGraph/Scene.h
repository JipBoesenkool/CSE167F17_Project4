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
#include "ControlPoint.h"

#include "../physics/BoundingVolume.h"
#include "../physics/BoundingSphere.h"

#include "../renderer/model/Model.h"
#include "../renderer/lighting/PointLightModel.h"

class Scene
{
//Members
private:
//Picking
	//Framebuffer for picking
	GLuint m_fbo, m_rbo, m_pbo;
	GLuint m_fboTexture;

	//Shaders

	//Main node
	TransformNode world;
	TransformNode *track;
	TransformNode *cart;
	GeometryNode *redSphere;
	GeometryNode *blueSphere;
	GeometryNode *metalicSphere;

	BezierHandleNode *handle0;
	BezierHandleNode *handle1;
	BezierHandleNode *handle2;
	BezierHandleNode *handle3;

	TransformNode *light2world;
	PointLightModel *pointLightObj;
	bool sceneLoaded = false;
public:
	std::vector<ControlPoint *> m_controlPoints;
//Functions
public:
	Scene();
	~Scene();

	virtual void Draw();
	virtual void Update();

	void InitPickingRenderBuffer();
	void RenderPickingToBuffer();
	void MouseSelect(double xpos, double ypos);
};


#endif //SCENE_H
