//
// Created by Jip Boesenkool on 09/11/2017.
//

#ifndef TRANSFORMNODE_H
#define TRANSFORMNODE_H

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif

// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Node.h"
#include "../renderer/model/Transform.h"
#include <list>

class TransformNode : public Node
{
//Members
public:
	Transform m_transform;
	std::list<Node*> m_children;
//Functions
public:
	TransformNode( )
	{
		//Empty constructor
	};

	TransformNode(const TransformNode &obj)
	{
		m_transform = obj.m_transform;
		m_children = obj.m_children;
	};

	~TransformNode( )
	{

	};

	void Draw(glm::mat4 C) override
	{
		glm::mat4 M_new = C * m_transform.GetModelMatrix();
		for(auto &n : m_children)
		{
			n->Draw(M_new);
		}
	};

	void Update() override
	{
		for(auto &n : m_children)
		{
			n->Update();
		}
	};

	void AddChild(Node *child)
	{
		m_children.push_back( child );
	};

	void RemoveChild( Node *child )
	{
		m_children.remove( child );
	};
};

#endif //TRANSFORMNODE_H
