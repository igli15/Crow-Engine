#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 diffuseColor;
uniform vec3 viewPos;

struct Light {

    vec3 direction;
    vec3 color;
};

void main()
{
    FragColor = vec4(diffuseColor,1);
}