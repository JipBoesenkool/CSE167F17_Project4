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
	PointLight m_pointLight;
//Functions
public:
	PointLightModel(GLuint shader, glm::vec3 position = glm::vec3(0));

	void Draw() override;
	void Update() override;
};


#endif //POINTLIGHTMODEL_H
