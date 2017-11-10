#include "CubeMapModel.h"

CubeMapModel::CubeMapModel(GLuint shader, const char* filepath)
		: Model("../resources/models/cube.obj", shader)
{
	m_shader = shader;
	m_local.m_position = glm::vec3(0.0f);
	m_local.Scale(500.0f);

	//Set up skybox shader
	glUseProgram(shader);
	LoadCubemap(filepath, m_faces);
}

void CubeMapModel::Draw( )
{
	glDepthMask(GL_FALSE);
	glUseProgram(m_shader);

	glBindVertexArray(m_VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	Model::Draw();

	glDepthMask(GL_TRUE);
}

void CubeMapModel::Update()
{
	//Empty
}

void CubeMapModel::LoadCubemap(const char* filepath ,std::vector<std::string> faces)
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		sf::Image img;
		std::string file = filepath + faces[i];
		if (img.loadFromFile( file ))
		{
			glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0,
					GL_RGBA,
					img.getSize().x, img.getSize().y,
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					img.getPixelsPtr()
			);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
		}
	}
	// Use bilinear interpolation:
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Use clamp to edge to hide skybox edges:
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
