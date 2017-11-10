#ifndef GEOMETRYNODE_H
#define GEOMETRYNODE_H

#include "../renderer/model/Model.h"

class GeometryNode : public Node
{
//Members
public:
	Model *m_model;
//Functions
public:
	GeometryNode( )
	{
		//Empty constructor
	};

	GeometryNode( Model *model )
	{
		m_model = model;
	};

	GeometryNode( const char* filepath, unsigned int shader )
	{
		m_model = new Model(filepath, shader);
	};

	void Init(const char* filepath, unsigned int shader)
	{
		m_model = new Model(filepath, shader);
	}

	void Draw(glm::mat4 C) override
	{
		m_model->m_local.m_matrix = C * m_model->m_local.GetModelMatrix();
		m_model->Draw();
	};

	void Update() override
	{
		m_model->Update();
	};
};

#endif //GEOMETRYNODE_H
