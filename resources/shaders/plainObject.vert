#version 330 core
// NOTE: Do NOT use any version older than 330! Bad things will happen!

// This is an example vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

// Uniform variables can be updated by fetching their location and passing values to that location
uniform vec3 color;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT
{
    vec3 color;
} vs_out;

void main()
{
    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
    vs_out.color = color;
}
