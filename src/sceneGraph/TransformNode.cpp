//
// Created by Jip Boesenkool on 12/11/2017.
//
#include "TransformNode.h"
#include "../Window.h"

//Functions public:
TransformNode::TransformNode( )
{
	//Empty constructor
}

TransformNode::TransformNode(const TransformNode &obj)
{
	m_transform = obj.m_transform;
	m_children = obj.m_children;
	m_bVolume = obj.m_bVolume;
}

TransformNode::~TransformNode( )
{
	//Empty deconstructor
}

void TransformNode::Draw(glm::mat4 C)
{
	glm::mat4 M_new = C * m_transform.GetModelMatrix();
	if(m_bVolume != nullptr)
	{
		//Check bounds
		if( Window::cull && !m_bVolume->Cull(M_new) )
		{
			//outside of frustum
			return;
		}
		else
		{
			//Render bounds
			m_bVolume->Draw(M_new);
		}
	}

	//Render children
	for(auto &n : m_children)
	{
		n->Draw(M_new);
	}
}

void TransformNode::Update()
{
	for(auto &n : m_children)
	{
		n->Update();
	}
}

void TransformNode::AddChild(Node *child)
{
	m_children.push_back( child );
}

void TransformNode::RemoveChild( Node *child )
{
	m_children.remove( child );
}
