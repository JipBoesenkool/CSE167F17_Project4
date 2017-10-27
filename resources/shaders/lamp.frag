#version 330 core

in VS_OUT
{
    vec3 color;
} fs_in;

out vec4 color;

void main()
{
    color = vec4(fs_in.color, 0.7f); // Set alle 4 vector values to 1.0f
}