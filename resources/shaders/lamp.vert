#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec3 texCoords;

uniform vec3 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT
{
    vec3 color;
} vs_out;

void main()
{
    vs_out.color = color;
    gl_Position = projection * view * model * vec4(position, 1.0f);
}