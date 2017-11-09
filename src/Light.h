#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>


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

struct Light {
    glm::vec3 m_position;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    void SetUniform(GLint shader)
    {
        GLint lightPositionLoc = glGetUniformLocation(shader, "light.position");
        GLint lightAmbientLoc  = glGetUniformLocation(shader, "light.ambient");
        GLint lightDiffuseLoc  = glGetUniformLocation(shader, "light.diffuse");
        GLint lightSpecularLoc = glGetUniformLocation(shader, "light.specular");

        glUniform3f(lightPositionLoc, m_position.x, m_position.y, m_position.z);
        glUniform3f(lightAmbientLoc,  m_ambient.x,  m_ambient.y,  m_ambient.z);
        glUniform3f(lightDiffuseLoc,  m_diffuse.x,  m_diffuse.y,  m_diffuse.z);
        glUniform3f(lightSpecularLoc, m_specular.x, m_specular.y, m_specular.z);
    }

    void SetUniform(GLint shader, int index)
    {
        std::string number = std::to_string(index);

        GLint lightPositionLoc = glGetUniformLocation(shader, ("lights[" + number + "].position").c_str() );
        GLint lightAmbientLoc  = glGetUniformLocation(shader, ("lights[" + number + "].ambient").c_str() );
        GLint lightDiffuseLoc  = glGetUniformLocation(shader, ("lights[" + number + "].diffuse").c_str() );
        GLint lightSpecularLoc = glGetUniformLocation(shader, ("lights[" + number + "].specular").c_str() );

        glUniform3f(lightPositionLoc, m_position.x, m_position.y, m_position.z);
        glUniform3f(lightAmbientLoc,  m_ambient.x,  m_ambient.y,  m_ambient.z);
        glUniform3f(lightDiffuseLoc,  m_diffuse.x,  m_diffuse.y,  m_diffuse.z);
        glUniform3f(lightSpecularLoc, m_specular.x, m_specular.y, m_specular.z);
    }
};

struct PointLight {
    glm::vec3 m_position;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    GLfloat m_constant;
    GLfloat m_linear;
    GLfloat m_quadratic;

    void SetUniform(GLint shader)
    {
		glUseProgram(shader);
		GLint lightDirLoc      = glGetUniformLocation(shader, "pointLight.position");
		GLint lightAmbientLoc  = glGetUniformLocation(shader, "pointLight.ambient");
		GLint lightDiffuseLoc  = glGetUniformLocation(shader, "pointLight.diffuse");
		GLint lightSpecularLoc = glGetUniformLocation(shader, "pointLight.specular");

		glUniform3f(lightDirLoc, m_position.x, m_position.y, m_position.z);
		glUniform3f(lightAmbientLoc,  m_ambient.x,   m_ambient.y,   m_ambient.z);
		glUniform3f(lightDiffuseLoc,  m_diffuse.x,   m_diffuse.y,   m_diffuse.z);
		glUniform3f(lightSpecularLoc, m_specular.x,  m_specular.y,  m_specular.z);

        GLint lightConstantLoc  = glGetUniformLocation(shader, "pointLight.constant");
        GLint lightLinearLoc    = glGetUniformLocation(shader, "pointLight.linear");
        GLint lightQuadraticLoc = glGetUniformLocation(shader, "pointLight.quadratic");
        glUniform1f(lightConstantLoc,  m_constant);
        glUniform1f(lightLinearLoc,    m_linear);
        glUniform1f(lightQuadraticLoc, m_quadratic);
    }
};

struct SpotLight {
    glm::vec3 m_position;
    glm::vec3 m_direction;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    GLfloat m_constant;
    GLfloat m_linear;
    GLfloat m_quadratic;

    GLfloat m_cutoff;
	GLfloat m_outercutoff;

    void SetUniform(GLint shader)
    {
		glUseProgram(shader);
        GLint lightPositionLoc  = glGetUniformLocation(shader, "spotLight.position");
        GLint lightDirectionLoc  = glGetUniformLocation(shader, "spotLight.direction");
        glUniform3f(lightPositionLoc, m_position.x, m_position.y, m_position.z);
        glUniform3f(lightDirectionLoc, m_direction.x, m_direction.y, m_direction.z);

        GLint lightAmbientLoc   = glGetUniformLocation(shader, "spotLight.ambient");
        GLint lightDiffuseLoc   = glGetUniformLocation(shader, "spotLight.diffuse");
        GLint lightSpecularLoc  = glGetUniformLocation(shader, "spotLight.specular");
        glUniform3f(lightAmbientLoc,  m_ambient.x,  m_ambient.y,  m_ambient.z);
        glUniform3f(lightDiffuseLoc,  m_diffuse.x,  m_diffuse.y,  m_diffuse.z);
        glUniform3f(lightSpecularLoc, m_specular.x, m_specular.y, m_specular.z);

        GLint lightConstantLoc  = glGetUniformLocation(shader, "spotLight.constant");
        GLint lightLinearLoc    = glGetUniformLocation(shader, "spotLight.linear");
        GLint lightQuadraticLoc = glGetUniformLocation(shader, "spotLight.quadratic");
        glUniform1f(lightConstantLoc,  m_constant);
        glUniform1f(lightLinearLoc,    m_linear);
        glUniform1f(lightQuadraticLoc, m_quadratic);

        GLint lightCutoffLoc = glGetUniformLocation(shader, "spotLight.cutoff");
        glUniform1f(lightCutoffLoc, glm::cos( glm::radians(m_cutoff) ) );
		GLint lightOuterCutoffLoc = glGetUniformLocation(shader, "spotLight.outercutoff");
		glUniform1f(lightOuterCutoffLoc, glm::cos( glm::radians(m_outercutoff) ) );
    }
};

struct DirLight {
    glm::vec3 m_direction;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    void SetUniform(GLint shader)
    {
		glUseProgram(shader);
        GLint lightDirLoc      = glGetUniformLocation(shader, "dirLight.direction");
        GLint lightAmbientLoc  = glGetUniformLocation(shader, "dirLight.ambient");
        GLint lightDiffuseLoc  = glGetUniformLocation(shader, "dirLight.diffuse");
        GLint lightSpecularLoc = glGetUniformLocation(shader, "dirLight.specular");

        glUniform3f(lightDirLoc, m_direction.x, m_direction.y, m_direction.z);
        glUniform3f(lightAmbientLoc,  m_ambient.x,   m_ambient.y,   m_ambient.z);
        glUniform3f(lightDiffuseLoc,  m_diffuse.x,   m_diffuse.y,   m_diffuse.z);
        glUniform3f(lightSpecularLoc, m_specular.x,  m_specular.y,  m_specular.z);
    }
};

#endif //LIGHT_H
