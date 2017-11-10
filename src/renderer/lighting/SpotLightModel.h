//
// Created by Jip Boesenkool on 26/10/2017.
//

#ifndef SPOTLIGHTMODEL_H
#define SPOTLIGHTMODEL_H

#include "../model/Model.h"
#include "Light.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

class SpotLightModel : public Model
{
//Members
public:
	SpotLight m_spotLight;
//Functions
public:
	SpotLightModel(GLuint shader, Transform *transform);

	void Draw( glm::mat4 m ) override;
	void Update() override;
};

#endif //SPOTLIGHTMODEL_H
