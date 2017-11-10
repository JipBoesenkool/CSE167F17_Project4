#ifndef CUBEMAPMODEL_H
#define CUBEMAPMODEL_H

#include <vector>
#include "Model.h"
#include <SFML/Graphics/Image.hpp>

class CubeMapModel : public Model
{
//Members
public:
	GLuint m_textureID;
private:
	std::vector<std::string> m_faces{
			"/right.jpg",
			"/left.jpg",
			"/top.jpg",
			"/bottom.jpg",
			"/back.jpg",
			"/front.jpg"
	};
//Functions
public:
	CubeMapModel(GLuint shader, const char* filepath, Transform *transform);

	void Draw( glm::mat4 m ) override;
	void Update() override;

private:
	void LoadCubemap(const char* filepath ,std::vector<std::string> faces);
};


#endif //CUBEMAPMODEL_H
