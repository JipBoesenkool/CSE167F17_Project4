//
// Created by Jip Boesenkool on 27/11/2017.
//
#ifndef BEZIERHANDLENODE_H
#define BEZIERHANDLENODE_H

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

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformNode.h"
#include "../renderer/model/Transform.h"

class BezierHandleNode : public TransformNode
{
//Members
public:
	//Control points
	Transform *m_c0;
	Transform *m_c1;
	Transform *m_p0;

	//Line intersecting point
	BezierHandleNode *m_prev = nullptr;
	BezierHandleNode *m_next = nullptr;
	bool m_needsUpdate = true;

	std::vector<glm::vec3> m_vertices;

	// These variables are needed for the shader program
	//Opengl
	GLuint m_VBO, m_VAO;
	GLuint m_handleVBO, m_handleVAO;
	glm::vec3 controlPoints[2];

//Functions
public:
	BezierHandleNode( Transform *c0, Transform *p0, Transform *c1 );
	BezierHandleNode( Transform *c0, Transform *p0, Transform *c1, BezierHandleNode *next );
	~BezierHandleNode( );

	virtual void Draw(glm::mat4 C) override;
	virtual void Update() override;

	void IsDirty();
	void SetPrev( BezierHandleNode *prev );
	void SetNext( BezierHandleNode *next );

	void CalculateBezierCurve();
	glm::vec3 BezierCurvePoint(float t);
	glm::vec3 BezierCurvePoint(float t, glm::vec3 P0, glm::vec3 P1, glm::vec3 P2, glm::vec3 P3);
	float BezierCurvePoint(float t, float P0, float P1, float P2, float P3);
};

#endif //BEZIERHANDLENODE_H
