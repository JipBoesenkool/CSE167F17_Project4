#version 330 core

uniform vec3 viewPos;
uniform samplerCube skybox;

in VS_OUT
{
    vec3 normal;
    vec3 position;
} fs_in;

//The first vec4 type output determines the color of the fragment
out vec4 color;

void main()
{
    vec3 I = normalize(fs_in.position - viewPos);
    vec3 R = reflect(I, normalize(fs_in.normal));
    color = vec4( texture(skybox, R).rgb, 1.0);
}
