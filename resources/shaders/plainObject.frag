#version 330 core

in VS_OUT
{
    vec3 color;
} fs_in;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;

void main()
{
    color = fs_in.color;
}
