//
// Created by Jip Boesenkool on 26/10/2017.
//

#ifndef POINTLIGHTMODEL_H
#define POINTLIGHTMODEL_H

#include "../model/Model.h"
#include "Light.h"

class PointLightModel : public Model
{
//Members
public:
	GLuint m_phongShader;
	Transform *m_transform;
	PointLight m_pointLight;
//Functions
public:
	PointLightModel(GLuint phongShader, GLuint shader, Transform *transform);

	void Draw( glm::mat4 m ) override;
	void Update() override;
};


#endif //POINTLIGHTMODEL_H
