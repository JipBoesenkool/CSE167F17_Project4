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
	TransformNode *robot2world = new TransformNode();

	Model *bunny = new Model("../resources/models/bunny.obj", Window::shaderPhongProgram);
	bunny->m_material = Material{
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			76.8f
	};
	glUseProgram(Window::shaderPhongProgram);
	bunny->m_material.SetUniform(Window::shaderPhongProgram);
	robot2world->AddChild( new GeometryNode( bunny ) );
	//robot2world.AddChild();

	//Add robot to world
	world.AddChild( robot2world );
}

void Scene::Draw()
{
	world.Draw( glm::mat4(1.0f) );
}

void Scene::Update()
{
	std::cout<<"scene::update"<<std::endl;
	world.Update();
}