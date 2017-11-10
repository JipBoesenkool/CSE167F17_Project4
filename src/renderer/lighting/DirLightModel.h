//
// Created by Jip Boesenkool on 26/10/2017.
//

#ifndef DIRLIGHTMODEL_H
#define DIRLIGHTMODEL_H

#include "../model/Model.h"
#include "Light.h"

class DirLightModel : public Model
{
//Members
public:
	DirLight m_dirLight;
//Functions
public:
	DirLightModel(GLuint shader, Transform *transform);

	void Draw( glm::mat4 m ) override;
	void Update() override;
};


#endif //DIRLIGHTMODEL_H
