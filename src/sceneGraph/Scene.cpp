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

	//Create robot:
	robot2world = new TransformNode();

//Test
	Model *bunny = new Model("../resources/models/bunny.obj", Window::shaderPhongProgram, &robot2world->m_transform);
	bunny->m_material = Material{
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			76.8f
	};
	glUseProgram(Window::shaderPhongProgram);
	bunny->m_material.SetUniform(Window::shaderPhongProgram);
	robot2world->AddChild( new GeometryNode( bunny ) );
	robot2world->m_transform.Move( glm::vec3(5.0f, 0.0f, 0.0f) );

	robot2world->m_transform.m_localOrientation = false;

	bunny2robot = new TransformNode();
	bunny2robot->m_transform.Move( glm::vec3(0.0f, 5.0f, 0.0f) );
	bunny2robot->AddChild( new GeometryNode( bunny ) );
	robot2world->AddChild( bunny2robot );
//End test

//Lighting
	light2world = new TransformNode(  );
	light2world->m_transform.Move( glm::vec3(5.0f, 0.0f, 1.0f) );
	pointLightObj = new PointLightModel(Window::shaderPhongProgram, &light2world->m_transform);
	light2world->AddChild( new GeometryNode( pointLightObj ) );

	world.AddChild( light2world );

//End Lighting

	//Add robot to world
	world.AddChild( robot2world );
}

void Scene::Draw()
{
	robot2world->m_transform.Rotate( glm::vec3(0, 1.0f, 0) );
	world.Draw( glm::mat4(1.0f) );
}

void Scene::Update()
{
	world.Update();
}