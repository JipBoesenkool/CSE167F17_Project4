//
// Created by Jip Boesenkool on 27/11/2017.
//

#include "ControlPoint.h"
ControlPoint::ControlPoint( GeometryNode *geoNode )
{
	m_geoNode = geoNode;
}

ControlPoint::~ControlPoint( )
{
	//Empty deconstructor
}

void ControlPoint::Draw(glm::mat4 C)
{
	m_storedMatrix = C * m_transform.GetModelMatrix();
	TransformNode::Draw( C );
}

void ControlPoint::Update()
{
	TransformNode::Update( );
}

void ControlPoint::Move( glm::vec3 dir )
{
	//Constrain the other control node
	if(m_cpPaired != nullptr)
	{
		//Move this node
		m_transform.Move( dir );
		glm::vec3 cpDirVec = m_transform.m_position - m_parent->m_p0->m_position;
		m_cpPaired->m_transform.SetPosition( ( (-cpDirVec) + m_parent->m_p0->m_position) );
	}
	else
	{
		//Make control point relative
		m_parent->m_c0->m_position = m_parent->m_c0->m_position - m_transform.m_position;
		m_parent->m_c1->m_position = m_parent->m_c1->m_position - m_transform.m_position;
		//Move node
		m_transform.Move( dir );
		//Translate control nodes to world space
		m_parent->m_c0->SetPosition( (m_parent->m_c0->m_position + m_transform.m_position) );
		m_parent->m_c1->SetPosition( (m_parent->m_c1->m_position + m_transform.m_position) );
	}

	//Notify parent it has to recalculate
	m_parent->IsDirty();
}