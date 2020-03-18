#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 mainColor;
uniform vec3 viewPos;

struct Light {

    vec3 direction;
    vec3 color;
};

struct Material
{
    vec3 mainColor;
    vec3 specularColor;
    float ambientIntensity;
    float shininess;
};

uniform Light light;
uniform Material material;

void main()
{
        //ambient
        vec3 ambient = material.ambientIntensity * light.color;

        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, light.direction), 0.0);
        vec3 diffuse = diff * light.color;

        // specular
        float specularStrength = 0.8;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-light.direction, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = material.specularColor * spec * light.color;

        vec3 result = (ambient + diffuse + specular) * material.mainColor;
        FragColor = vec4(result, 1.0);
}