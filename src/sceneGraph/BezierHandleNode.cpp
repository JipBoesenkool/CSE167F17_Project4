//
// Created by Jip Boesenkool on 27/11/2017.
//
#include "BezierHandleNode.h"
#include "../Window.h"

BezierHandleNode::BezierHandleNode( Transform *c0, Transform *p0, Transform *c1 )
{
	m_c0 = c0;
	m_p0 = p0;
	m_c1 = c1;
}

BezierHandleNode::BezierHandleNode( Transform *c0, Transform *p0, Transform *c1, BezierHandleNode *next )
{
	m_c0 = c0;
	m_p0 = p0;
	m_c1 = c1;
	SetNext( next );
}

BezierHandleNode::~BezierHandleNode( )
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

void BezierHandleNode::Draw(glm::mat4 C)
{
	//Render line of handle
	glUseProgram(Window::shaderLineProgram);
	GLint uModel 		= glGetUniformLocation(Window::shaderLineProgram, "model");
	glUniformMatrix4fv(uModel, 1, GL_FALSE, &C[0][0]);
	GLint uColor 		= glGetUniformLocation(Window::shaderLineProgram, "color");
	glUniform4f(uColor, 1.0f, 0.0f, 0.0f, 1.0f);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_LINES,0,2);
	glBindVertexArray(0);

	if(m_next != nullptr)
	{
		//Draw curve
		glUseProgram(Window::shaderLineProgram);
		GLint uColor 		= glGetUniformLocation(Window::shaderLineProgram, "color");
		glUniform4f(uColor, 0.0f, 0.0f, 0.0f, 1.0f);

		glBindVertexArray(m_handleVAO);
		glDrawArrays(GL_LINE_STRIP, 0, m_vertices.size() );
		glBindVertexArray(0);
	}

	TransformNode::Draw(C);
}

void BezierHandleNode::Update()
{
	//Update when moved.
	if( m_needsUpdate )
	{
		//Set handle
		//TODO: set constraint by giving them one transform?
		controlPoints[0] = m_c0->m_position;
		controlPoints[1] = m_c1->m_position;

//Set opengl handle
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(controlPoints), &controlPoints[0], GL_STATIC_DRAW);

// Vertex Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		glEnableVertexAttribArray(0);
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindVertexArray(0);

		glUseProgram(Window::shaderLineProgram);
		GLint uColor 		= glGetUniformLocation(Window::shaderLineProgram, "color");
		glUniform4f(uColor, 1.0f, 0.0f, 0.0f, 1.0f);

		if(m_next != nullptr && m_prev != nullptr)
		{
			//Recalculate curve
			CalculateBezierCurve();
			m_prev->m_needsUpdate = true;

			//Set opengl handle
			glGenVertexArrays(1, &m_handleVAO);
			glGenBuffers(1, &m_handleVBO);
			glBindVertexArray(m_handleVAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_handleVBO);
			glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat) * 3, m_vertices.data(), GL_STATIC_DRAW);

// Vertex Positions
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

			glEnableVertexAttribArray(0);
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glBindVertexArray(0);
		}

		m_needsUpdate = false;
	}
	TransformNode::Update();
}

void BezierHandleNode::IsDirty()
{
	m_needsUpdate = true;
}

void BezierHandleNode::SetNext( BezierHandleNode *next )
{
	m_next = next;
	m_needsUpdate = true;
}

void BezierHandleNode::CalculateBezierCurve()
{
	m_vertices.clear();
	glm::vec3 p2 = m_next->m_c0->m_position;
	glm::vec3 p3 = m_next->m_p0->m_position;
	for (int i = 0; i < 30; i++) {
		float t = i / 30.0f;
		// Gives us our midpoint
		m_vertices.push_back(
				BezierCurvePoint(t, m_p0->m_position, m_c1->m_position, p2, p3)
		);
	}
}

glm::vec3 BezierHandleNode::BezierCurvePoint(float t)
{
	glm::vec3 p2 = m_next->m_c0->m_position;
	glm::vec3 p3 = m_next->m_p0->m_position;
	return BezierCurvePoint(t, m_p0->m_position, m_c1->m_position, p2, p3);
}

glm::vec3 BezierHandleNode::BezierCurvePoint(float t, glm::vec3 P0, glm::vec3 P1, glm::vec3 P2, glm::vec3 P3)
{
	return glm::vec3(
			BezierCurvePoint(t, P0.x, P1.x, P2.x, P3.x),
			BezierCurvePoint(t, P0.y, P1.y, P2.y, P3.y),
			BezierCurvePoint(t, P0.z, P1.z, P2.z, P3.z)
	);
}

float BezierHandleNode::BezierCurvePoint(float t, float P0, float P1, float P2, float P3)
{
	// formula from https://en.wikipedia.org/wiki/Bézier_curve
	float point = (pow((1-t), 3.0) * P0) +
				  (3 * pow((1-t),2) * t * P1) +
				  (3 * (1-t) * t * t * P2) +
				  (pow(t, 3) * P3);
	return point;
}
