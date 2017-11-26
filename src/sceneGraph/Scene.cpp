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

//Robot
	//Create robot:
	robot2world = new TransformNode();
	robot2world->m_bVolume = new BoundingSphere( &robot2world->m_transform );

	floor2world = new TransformNode();
	Model *head = new Model("../resources/models/robot-parts/head.obj", Window::shaderNormalProgram, &robot2world->m_transform);
	Model *eyeball = new Model("../resources/models/robot-parts/eyeball.obj", Window::shaderNormalProgram, &robot2world->m_transform);
	Model *limb = new Model("../resources/models/robot-parts/limb.obj", Window::shaderNormalProgram, &robot2world->m_transform);
	Model *ant = new Model("../resources/models/robot-parts/antenna.obj", Window::shaderNormalProgram, &robot2world->m_transform);
	Model *plane = new Model("../resources/models/plane.obj", Window::shaderPhongProgram, &floor2world->m_transform);
	plane->m_material = Material{
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(1.0f, 0.5f, 0.31f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			76.8f
	};
	glUseProgram(Window::shaderPhongProgram);
	plane->m_material.SetUniform(Window::shaderPhongProgram);

	floor2world->AddChild( new GeometryNode( plane ) );
	floor2world->m_transform.Move( glm::vec3(0.0f, -1.0f, 0.0f) );
	floor2world->m_transform.Scale( 100.0f );
	world.AddChild(floor2world);

	//Limb
	limb2robot = new TransformNode( );
	limb2robot->m_transform.m_position = glm::vec3(-0.8f, 1.0f, 0.0f);
	limb2robot->AddChild( new GeometryNode( limb ) );
	robot2world->AddChild(limb2robot);

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
//End robot

// Robot Army (15 Points)
	//Amount, 1 = 100
	float amount = 5;
	for( int x = -20*amount; x < 20*amount ; x = x + 4 ) {
		for( int z = -20*amount; z < 20*amount ; z = z + 4 ) {
			TransformNode *next = new TransformNode( *robot2world );
			next->m_transform.m_position = glm::vec3( x, 0, z );
			next->m_bVolume->m_transform->m_position = glm::vec3( x, 0, z );
			world.AddChild( next );
		}
	}

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
//Test
	/*
	robot2world->m_transform.Rotate( glm::vec3(0, 1.0f, 0) );
	bunny2robot->m_transform.Rotate( glm::vec3(0, 1.0f, 0) );
	 */
//End test
	body2robot->m_transform.Rotate( glm::vec3(-1.0f, 0.0f, 0.0f) );
	head2robot->m_transform.Rotate( glm::vec3(0.0f, 0.0f, 1.0f) );
	eye2head->m_transform.Rotate( glm::vec3(0.0f, 0.0f, 1.0f) );
	//limb2robot->m_transform.Rotate( glm::vec3(1.0f, 0.0f, 0.0f) );

	world.Draw( glm::mat4(1.0f) );
}

void Scene::Update()
{
	if(!sceneLoaded)
	{
		return;
	}

	world.Update();

	if(bullets2world != nullptr)
	{
		bullets2world->m_transform.Move( glm::vec3(0.0f, 0.0f, 1.0f) );

		if(bullets2world->m_transform.m_position.z > 100.0f)
		{
			//Disable lights
			glUseProgram(Window::shaderPhongProgram);
			GLint lightCounterLoc = glGetUniformLocation(Window::shaderPhongProgram, "nrLights" );
			glUniform1ui(lightCounterLoc, 0);

			world.RemoveChild(bullets2world);
			delete(bullets2world);
			bullets2world = nullptr;
		}
	}
}

void Scene::Fire()
{
	if(bullets2world == nullptr)
	{
		//Add bullet node
		bullets2world = new TransformNode();
		bullets2world->m_transform.m_position = glm::vec3(-0.8f, 1.0f, 0.0f);
		for(Node *n : world.m_children)
		{
			TransformNode *node = (TransformNode *)n;
			TransformNode *bullet = new TransformNode( *light2world );
			bullet->m_transform.m_position = glm::vec3( node->m_transform.m_position );
			bullets2world->AddChild( bullet );
		}
		world.AddChild(bullets2world);

		//Update shader
		glUseProgram(Window::shaderPhongProgram);
		for(int i = 0; i < 100; i++)
		{
			pointLightObj->m_pointLight.SetUniform( Window::shaderPhongProgram, i );
		}
		GLint lightCounterLoc = glGetUniformLocation(Window::shaderPhongProgram, "nrLights" );
		glUniform1ui(lightCounterLoc, 100);
	}
}