#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 mainColor;
uniform sampler2D diffuseTexture;

void main()
{
    vec3 norm = normalize(Normal);

    vec3 result = mainColor * texture(diffuseTexture,TexCoords).rgb;

    FragColor = vec4(result, 1.0);
}
