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

	~GeometryNode( )
	{
		//Empty constructor
	};

	GeometryNode( const char* filepath, unsigned int shader, Transform *transform )
	{
		m_model = new Model(filepath, shader, transform);
	};

	void Init(const char* filepath, unsigned int shader, Transform *transform)
	{
		m_model = new Model(filepath, shader, transform);
	}

	void Draw(glm::mat4 C) override
	{
		m_model->Draw(C);
	};

	void Update() override
	{
		m_model->Update();
	};
};

#endif //GEOMETRYNODE_H
