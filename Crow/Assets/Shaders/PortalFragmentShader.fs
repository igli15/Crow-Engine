#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform float time;
uniform vec3 mainColor;

void main()
{
    vec3 norm = normalize(Normal);
    FragColor = vec4(mainColor ,1.0) ;
}
