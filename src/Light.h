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

/*
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
 */

struct PointLight {
    glm::vec3 m_position;
	glm::vec3 m_color;
    void SetUniform(GLint shader)
    {
		glUseProgram(shader);
        GLint lightPositionLoc  = glGetUniformLocation(shader, "light.position");
        glUniform3f(lightPositionLoc, m_position.x, m_position.y, m_position.z);
		GLint colorPositionLoc  = glGetUniformLocation(shader, "light.color");
		glUniform3f(lightPositionLoc, m_color.r, m_color.g, m_color.b);

		/*
        GLint lightAmbientLoc   = glGetUniformLocation(shader, "light.ambient");
        GLint lightDiffuseLoc   = glGetUniformLocation(shader, "light.diffuse");
        GLint lightSpecularLoc  = glGetUniformLocation(shader, "light.specular");
        glUniform3f(lightAmbientLoc,  m_ambient.x,  m_ambient.y,  m_ambient.z);
        glUniform3f(lightDiffuseLoc,  m_diffuse.x,  m_diffuse.y,  m_diffuse.z);
        glUniform3f(lightSpecularLoc, m_specular.x, m_specular.y, m_specular.z);

        GLint lightConstantLoc  = glGetUniformLocation(shader, "light.constant");
        GLint lightLinearLoc    = glGetUniformLocation(shader, "light.linear");
        GLint lightQuadraticLoc = glGetUniformLocation(shader, "light.quadratic");
        glUniform1f(lightConstantLoc,  m_constant);
        glUniform1f(lightLinearLoc,    m_linear);
        glUniform1f(lightQuadraticLoc, m_quadratic);
        */
    }
};

struct SpotLight {
    //glm::vec3 m_position;
	glm::vec3 m_color;
    glm::vec3 m_direction;
    GLfloat m_cutoffAngle;
	GLfloat m_exponent;

	/*
    void SetUniform(GLint shader)
    {
		glUseProgram(shader);
        GLint lightPositionLoc  = glGetUniformLocation(shader, "light.position");
        GLint lightDirectionLoc  = glGetUniformLocation(shader, "light.direction");
        glUniform3f(lightPositionLoc, m_position.x, m_position.y, m_position.z);
        glUniform3f(lightDirectionLoc, m_direction.x, m_direction.y, m_direction.z);

        GLint lightAmbientLoc   = glGetUniformLocation(shader, "light.ambient");
        GLint lightDiffuseLoc   = glGetUniformLocation(shader, "light.diffuse");
        GLint lightSpecularLoc  = glGetUniformLocation(shader, "light.specular");
        glUniform3f(lightAmbientLoc,  m_ambient.x,  m_ambient.y,  m_ambient.z);
        glUniform3f(lightDiffuseLoc,  m_diffuse.x,  m_diffuse.y,  m_diffuse.z);
        glUniform3f(lightSpecularLoc, m_specular.x, m_specular.y, m_specular.z);

        GLint lightConstantLoc  = glGetUniformLocation(shader, "light.constant");
        GLint lightLinearLoc    = glGetUniformLocation(shader, "light.linear");
        GLint lightQuadraticLoc = glGetUniformLocation(shader, "light.quadratic");
        glUniform1f(lightConstantLoc,  m_constant);
        glUniform1f(lightLinearLoc,    m_linear);
        glUniform1f(lightQuadraticLoc, m_quadratic);

        GLint lightCutoffLoc = glGetUniformLocation(shader, "light.cutoff");
        glUniform1f(lightCutoffLoc, glm::cos( glm::radians(m_cutoffAngle) ) );
    }
    */
};

struct DirLight {
    glm::vec3 m_direction;
	glm::vec3 m_color;

	/*
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
    */
};

#endif //LIGHT_H
