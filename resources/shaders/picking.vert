#version 330 core
layout (location = 0) in vec3 position;

// Uniform variables can be updated by fetching their location and passing values to that location
uniform vec4 color;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT
{
    vec4 color;
} vs_out;

void main()
{
    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
    vs_out.color = color;
}
