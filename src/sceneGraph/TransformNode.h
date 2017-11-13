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
#include "../physics/BoundingVolume.h"
#include <list>

class TransformNode : public Node
{
//Members
public:
	Transform m_transform;
	BoundingVolume *m_bVolume = nullptr;
	std::list<Node*> m_children;
//Functions
public:
	TransformNode( );
	TransformNode(const TransformNode &obj);
	~TransformNode( );

	void Draw(glm::mat4 C) override;
	void Update() override;

	void AddChild(Node *child);
	void RemoveChild( Node *child );
};

#endif //TRANSFORMNODE_H
