#ifndef MATERIAL_H
#define MATERIAL_H

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shader.h"

struct Material {
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    float m_shininess;

    void SetUniform(GLint shader)
    {
        GLint matAmbientLoc  = glGetUniformLocation(shader, "material.ambient");
        GLint matDiffuseLoc  = glGetUniformLocation(shader, "material.diffuse");
        GLint matSpecularLoc = glGetUniformLocation(shader, "material.specular");
        GLint matShineLoc    = glGetUniformLocation(shader, "material.shininess");

        glUniform3f(matAmbientLoc,  m_ambient.x,  m_ambient.y,  m_ambient.z);
        glUniform3f(matDiffuseLoc,  m_diffuse.x,  m_diffuse.y,  m_diffuse.z);
        glUniform3f(matSpecularLoc, m_specular.x, m_specular.y, m_specular.z);
        glUniform1f(matShineLoc,    m_shininess);
    }
};


#endif //MATERIAL_H
