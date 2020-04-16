#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 mainColor;
uniform vec3 viewPos;

struct DirLight
{
    vec3 direction;
    vec3 color;
    float intensity;
};

struct PointLight
{
    vec3 position;
    vec3 color;

    float intensity;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 color;
    vec3 position;
    vec3 direction;

    float intensity;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};


struct Material
{
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    vec3 mainColor;
    vec3 specularColor;
    float ambientIntensity;
    float shininess;
};

#define NR_DIR_LIGHTS 20
uniform DirLight dirLights[NR_DIR_LIGHTS];

#define NR_POINT_LIGHTS 20
uniform PointLight pointLights[NR_POINT_LIGHTS];

#define NR_SPOT_LIGHTS 20
uniform SpotLight spotLights[NR_POINT_LIGHTS];

uniform Material material;

uniform int activeDirLights;
uniform int activePointLights;
uniform int activeSpotLights;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result;

    for(int i = 0; i < activeDirLights; i++)
    {
        result += CalcDirLight(dirLights[i],norm,viewDir) * dirLights[i].intensity;
    }

    for(int i = 0; i < activePointLights; i++)
    {
        result += CalcPointLight(pointLights[i],norm,FragPos,viewDir) * pointLights[i].intensity;
    }

    for(int i = 0; i < activeSpotLights; i++)
    {
        result += CalcSpotLight(spotLights[i],norm,FragPos,viewDir) * spotLights[i].intensity;
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    vec3 ambient  = material.ambientIntensity * light.color;

    vec3 diffuseTex = vec3(texture(material.diffuseTexture,TexCoords));
    vec3 diffuse  = diff * light.color * diffuseTex;

    vec3 specularTex = vec3(texture(material.specularTexture,TexCoords));
    vec3 specular = material.specularColor * spec * light.color * specularTex;

    return (ambient + diffuse + specular) * material.mainColor;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
  			     light.quadratic * (distance * distance));

    vec3 ambient  = material.ambientIntensity * light.color;

    vec3 diffuseTex = vec3(texture(material.diffuseTexture,TexCoords));
    vec3 diffuse  = diff * light.color * diffuseTex;

    vec3 specularTex = vec3(texture(material.specularTexture,TexCoords));
    vec3 specular = material.specularColor * spec * light.color * specularTex;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular) * material.mainColor;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient  = material.ambientIntensity * light.color;

    vec3 diffuseTex = vec3(texture(material.diffuseTexture,TexCoords));
    vec3 diffuse  = diff * light.color * diffuseTex;

    vec3 specularTex = vec3(texture(material.specularTexture,TexCoords));
    vec3 specular = material.specularColor * spec * light.color * specularTex;

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular) * material.mainColor;
}