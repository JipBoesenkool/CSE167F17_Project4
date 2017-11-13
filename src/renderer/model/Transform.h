//
// Created by Jip Boesenkool on 26/10/2017.
//
#ifndef TRANSFORM_H
#define TRANSFORM_H

// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
	#define GLM_FORCE_RADIANS
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
//Members
private:
	bool m_updateMatrix = true;
public:
	bool m_localOrientation = true;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

//Getters & Setters
public:
	glm::mat4 m_matrix = glm::mat4(1.0f);
	glm::mat4 GetModelMatrix();
	glm::mat4 GetPositionMatrix();
	glm::mat4 GetRotationMatrix();
	glm::mat4 GetScaleMatrix();
//Functions
public:
	Transform(
			bool localOrientation = true,
			glm::vec3 position = glm::vec3(0.0f),
			glm::vec3 rotation = glm::vec3(0.0f),
			glm::vec3 scale = glm::vec3(1.0f));

	//Manipulation
	void SetPosition(glm::vec3 position);
	void Move(glm::vec3 direction);
	void Rotate(glm::vec3 rotation);
	void Scale(glm::vec3 scale);
	void Scale(float scale);

	void ResetPosition();
	void ResetRotation();
	void ResetScale();

private:
	void UpdateMatrix();
};

#endif //TRANSFORM_H
