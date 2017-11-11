//
// Created by Jip Boesenkool on 09/11/2017.
//

#ifndef NODE_H
#define NODE_H

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>

class Node
{
//Functions
public:
	virtual ~Node(){ };
	virtual void Draw(glm::mat4 C) = 0;
	virtual void Update() = 0;
};

#endif //NODE_H
