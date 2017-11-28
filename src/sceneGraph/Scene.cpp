//
// Created by Jip Boesenkool on 09/11/2017.
//

#include <iostream>
#include "Scene.h"
#include "../Window.h"

Scene::Scene()
{
	//Setup shaders

	//Setup scene

//Track
	track = new TransformNode();
	track->m_bVolume = new BoundingSphere( &track->m_transform );
	Model *redSphereModel = new Model("../resources/models/sphere.obj", Window::shaderPhongProgram, &track->m_transform);
	redSphereModel->m_material = Material{
			glm::vec3(0.5f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.9f, 0.6f, 0.6f),
			32.0f
	};
	Model *blueSphereModel = new Model("../resources/models/sphere.obj", Window::shaderPhongProgram, &track->m_transform);
	blueSphereModel->m_material = Material{
			glm::vec3(0.0f, 0.0f, 0.5f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.6f, 0.6f, 0.9f),
			32.0f
	};

	blueSphere = new GeometryNode( blueSphereModel );
	redSphere = new GeometryNode( redSphereModel );
//Set 0
	TransformNode *c00 = new TransformNode();
	c00->m_transform.m_position = glm::vec3(-2.0f, 1.0f, 0.0f);
	c00->m_transform.Scale(0.1f);
	c00->m_bVolume = new BoundingSphere( &c00->m_transform );
	c00->AddChild( redSphere );
	TransformNode *c01 = new TransformNode();
	c01->m_transform.m_position = glm::vec3(-1.0f, 2.0f, 0.0f);
	c01->m_transform.Scale(0.1f);
	c01->m_bVolume = new BoundingSphere( &c01->m_transform );
	c01->AddChild( redSphere );
	TransformNode *p0 = new TransformNode();
	p0->m_transform.m_position = glm::vec3(-1.5f, 1.5f, 0.0f);
	p0->m_transform.Scale(0.1f);
	p0->m_bVolume = new BoundingSphere( &p0->m_transform );
	p0->AddChild( blueSphere );
//Set 1
	TransformNode *c10 = new TransformNode();
	c10->m_transform.m_position = glm::vec3(1.0f, 2.0f, 0.0f);
	c10->m_transform.Scale(0.1f);
	c10->m_bVolume = new BoundingSphere( &c10->m_transform );
	c10->AddChild( redSphere );
	TransformNode *c11 = new TransformNode();
	c11->m_transform.m_position = glm::vec3(2.0f, 1.0f, 0.0f);
	c11->m_transform.Scale(0.1f);
	c11->m_bVolume = new BoundingSphere( &c11->m_transform );
	c11->AddChild( redSphere );
	TransformNode *p1 = new TransformNode();
	p1->m_transform.m_position = glm::vec3(1.5f, 1.5f, 0.0f);
	p1->m_transform.Scale(0.1f);
	p1->m_bVolume = new BoundingSphere( &p1->m_transform );
	p1->AddChild( blueSphere );
//Set 2
	TransformNode *c20 = new TransformNode();
	c20->m_transform.m_position = glm::vec3(2.0f, -1.0f, 0.0f);
	c20->m_transform.Scale(0.1f);
	c20->m_bVolume = new BoundingSphere( &c20->m_transform );
	c20->AddChild( redSphere );
	TransformNode *c21 = new TransformNode();
	c21->m_transform.m_position = glm::vec3(1.0f, -2.0f, 0.0f);
	c21->m_transform.Scale(0.1f);
	c21->m_bVolume = new BoundingSphere( &c21->m_transform );
	c21->AddChild( redSphere );
	TransformNode *p2 = new TransformNode();
	p2->m_transform.m_position = glm::vec3(1.5f, -1.5f, 0.0f);
	p2->m_transform.Scale(0.1f);
	p2->m_bVolume = new BoundingSphere( &p2->m_transform );
	p2->AddChild( blueSphere );
//Set 3
	TransformNode *c30 = new TransformNode();
	c30->m_transform.m_position = glm::vec3(-1.0f, -2.0f, 0.0f);
	c30->m_transform.Scale(0.1f);
	c30->m_bVolume = new BoundingSphere( &c30->m_transform );
	c30->AddChild( redSphere );
	TransformNode *c31 = new TransformNode();
	c31->m_transform.m_position = glm::vec3(-2.0f, -1.0f, 0.0f);
	c31->m_transform.Scale(0.1f);
	c31->m_bVolume = new BoundingSphere( &c31->m_transform );
	c31->AddChild( redSphere );
	TransformNode *p3 = new TransformNode();
	p3->m_transform.m_position = glm::vec3(-1.5f, -1.5f, 0.0f);
	p3->m_transform.Scale(0.1f);
	p3->m_bVolume = new BoundingSphere( &p3->m_transform );
	p3->AddChild( blueSphere );

//Set 3
	BezierHandleNode *handle3 = new BezierHandleNode(&c30->m_transform, &p3->m_transform, &c31->m_transform);
	handle3->AddChild(c30);
	handle3->AddChild(p3);
	handle3->AddChild(c31);
	track->AddChild(handle3);
//Set 2
	BezierHandleNode *handle2 = new BezierHandleNode(&c20->m_transform, &p2->m_transform, &c21->m_transform, handle3);
	handle2->AddChild(c20);
	handle2->AddChild(p2);
	handle2->AddChild(c21);
	track->AddChild(handle2);
//Set 1
	BezierHandleNode *handle1 = new BezierHandleNode(&c10->m_transform, &p1->m_transform, &c11->m_transform, handle2);
	handle1->AddChild(c10);
	handle1->AddChild(p1);
	handle1->AddChild(c11);
	track->AddChild(handle1);
//Set 0
	BezierHandleNode *handle0 = new BezierHandleNode(&c00->m_transform, &p0->m_transform, &c01->m_transform, handle1);
	handle0->AddChild(c00);
	handle0->AddChild(p0);
	handle0->AddChild(c01);
	handle3->SetNext( handle0 );

	track->AddChild(handle0);
	world.AddChild( track );
//End track

//Lighting
	light2world = new TransformNode(  );
	pointLightObj = new PointLightModel(Window::shaderPhongProgram, Window::shaderVisualLightProgram, &light2world->m_transform);
	light2world->AddChild( new GeometryNode( pointLightObj ) );
//End Lighting

	sceneLoaded = true;
}

Scene::~Scene()
{
	delete( &world );
}

void Scene::Draw()
{
	if(!sceneLoaded)
	{
		return;
	}
	world.Draw( glm::mat4(1.0f) );
}

void Scene::Update()
{
	if(!sceneLoaded)
	{
		return;
	}

	world.Update();
}