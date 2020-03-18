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

uniform Light light;

void main()
{
        //ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * light.color;

        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, light.direction), 0.0);
        vec3 diffuse = diff * light.color;

        // specular
        float specularStrength = 0.8;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-light.direction, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
        vec3 specular = specularStrength * spec * light.color;

        vec3 result = (ambient + diffuse + specular) * diffuseColor;
        FragColor = vec4(result, 1.0);
}