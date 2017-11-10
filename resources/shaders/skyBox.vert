#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    mat4 V = mat4(mat3(view));

    TexCoords = position;
    gl_Position = projection * V * model * vec4(position.xyz, 1.0);
}
