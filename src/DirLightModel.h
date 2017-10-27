//
// Created by Jip Boesenkool on 26/10/2017.
//

#ifndef DIRLIGHTMODEL_H
#define DIRLIGHTMODEL_H

#include "Model.h"
#include "Light.h"

class DirLightModel : public Model
{
//Members
public:
	DirLight m_dirLight;
	GLint m_shader;
//Functions
public:
	DirLightModel(GLuint shader, glm::vec3 position = glm::vec3(0));

	void Draw(GLuint shader) override;
	void Update() override;
};


#endif //DIRLIGHTMODEL_H
