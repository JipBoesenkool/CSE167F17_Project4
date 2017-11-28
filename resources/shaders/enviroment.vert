#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT
{
    vec3 normal;
    vec3 position;
} vs_out;

void main()
{
    vs_out.normal = mat3(transpose(inverse(model))) * normal;
    vs_out.position = vec3(model * vec4(position, 1.0));
    gl_Position = projection * view * model * vec4(position, 1.0);
}
