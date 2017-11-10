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

//Test
	/*
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

	bunny2robot = new TransformNode();
	bunny2robot->m_transform.Move( glm::vec3(0.0f, 5.0f, 0.0f) );
	bunny2robot->AddChild( new GeometryNode( bunny ) );
	robot2world->AddChild( bunny2robot );
	 */
//End test

	//Create robot:
	robot2world = new TransformNode();

	Model *head = new Model("../resources/models/robot-parts/head.obj", Window::shaderNormalProgram, &robot2world->m_transform);
	Model *eyeball = new Model("../resources/models/robot-parts/eyeball.obj", Window::shaderNormalProgram, &robot2world->m_transform);
	Model *limb = new Model("../resources/models/robot-parts/limb.obj", Window::shaderNormalProgram, &robot2world->m_transform);
	Model *ant = new Model("../resources/models/robot-parts/antenna.obj", Window::shaderNormalProgram, &robot2world->m_transform);

	//Body
	body2robot = new TransformNode( );
	body2robot->AddChild( new GeometryNode( eyeball ) );
	robot2world->AddChild(body2robot);

	//Head
	head2robot = new TransformNode( );
	head2robot->m_transform.m_position = glm::vec3(0.0f, 1.25f, 0.0f);
	head2robot->m_transform.m_rotation = glm::vec3(-90.0f, 0.0f, 0.0f);
	head2robot->m_transform.Scale(0.75f);
	head2robot->AddChild( new GeometryNode( head ) );
	robot2world->AddChild(head2robot);

	//Antenna
	ant2head = new TransformNode( );
	ant2head->m_transform.m_position = glm::vec3(0.0f, 0.0f, 0.25f);
	ant2head->m_transform.m_rotation = glm::vec3(0.0f, 45.0f, 0.0f);
	ant2head->m_transform.Scale(0.75f);
	ant2head->AddChild( new GeometryNode( ant ) );
	head2robot->AddChild(ant2head);

	//Eye
	eye2head = new TransformNode( );
	eye2head->m_transform.m_position = glm::vec3(0.0f, -0.75f, 0.25f);
	eye2head->m_transform.Scale(0.2f);
	eye2head->AddChild( new GeometryNode( eyeball ) );
	head2robot->AddChild(eye2head);

	//Limb
	limb2robot = new TransformNode( );
	limb2robot->m_transform.m_position = glm::vec3(-0.8f, 1.0f, 0.0f);
	limb2robot->AddChild( new GeometryNode( limb ) );
	robot2world->AddChild(limb2robot);
//Robot


//End robot

//Lighting
	light2world = new TransformNode(  );
	light2world->m_transform.Move( glm::vec3(4.0f, 0.0f, -1.0f) );
	pointLightObj = new PointLightModel(Window::shaderPhongProgram, Window::shaderVisualLightProgram, &light2world->m_transform);
	light2world->AddChild( new GeometryNode( pointLightObj ) );

	world.AddChild( light2world );

//End Lighting

	//Add robot to world
	world.AddChild( robot2world );
}

void Scene::Draw()
{
//Test
	/*
	robot2world->m_transform.Rotate( glm::vec3(0, 1.0f, 0) );
	bunny2robot->m_transform.Rotate( glm::vec3(0, 1.0f, 0) );
	 */
	body2robot->m_transform.Rotate( glm::vec3(-1.0f, 0.0f, 0.0f) );
	//head2robot->m_transform.Rotate( glm::vec3(0.0f, 0.0f, 1.0f) );
//End test

	world.Draw( glm::mat4(1.0f) );
}

void Scene::Update()
{
	world.Update();
}