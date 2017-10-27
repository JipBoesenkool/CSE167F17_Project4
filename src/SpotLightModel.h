//
// Created by Jip Boesenkool on 26/10/2017.
//

#ifndef SPOTLIGHTMODEL_H
#define SPOTLIGHTMODEL_H

#include "Model.h"
#include "Light.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

class SpotLightModel : public Model
{
//Members
public:
	SpotLight m_spotLight;
	GLint m_shader;
//Functions
public:
	SpotLightModel(GLuint shader, glm::vec3 position = glm::vec3(0));

	void Draw(GLuint shader) override;
	void Update() override;
};


#endif //SPOTLIGHTMODEL_H
