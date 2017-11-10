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

#include "Node.h"
#include <list>

class TransformNode : public Node
{
//Members
public:
	glm::mat4 m_M;
	std::list<Node*> m_children;
//Functions
public:
	TransformNode( )
	{
		m_M = glm::mat4(1.0f);
	};

	void Draw(glm::mat4 C) override
	{
		glm::mat4 M_new =C*m_M;
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
