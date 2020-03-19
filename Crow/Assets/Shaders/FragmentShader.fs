#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 mainColor;
uniform vec3 viewPos;

struct DirLight {

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

#define NR_DIR_LIGHTS 20
uniform DirLight dirLights[NR_DIR_LIGHTS];

uniform Material material;
uniform int activeDirLights;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result;

    for(int i = 0; i < activeDirLights; i++)
    {
        result += CalcDirLight(dirLights[i],norm,viewDir);
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = material.ambientIntensity * light.color;
    vec3 diffuse  = diff * light.color;
    vec3 specular = material.specularColor * spec * light.color;

    return (ambient + diffuse + specular) * material.mainColor;
}