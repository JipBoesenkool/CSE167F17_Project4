#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in float sampleExtraOutput;
in vec3 norm;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;

void main()
{
    vec3 offset = vec3(0.5f);
    // -1 * 0.5 = -0.5 + 0.5 = 0, 1 * 0.5 = 0.5 + 0.5 = 1
    vec3 normal = (offset * normalize( norm) ) + offset;
    // Color everything a hot pink color. An alpha of 1.0f means it is not transparent.
    color = vec4(normal, sampleExtraOutput);
}
