//
// Created by Igli milaqi on 14/04/2020.
//

#ifndef CROW_TEXTUREMATERIAL_H
#define CROW_TEXTUREMATERIAL_H

#include "../AbstractMaterial.h"
#include "../Texture.h"

class ResourceManager;

class TextureMaterial : public AbstractMaterial
{

public:
    TextureMaterial();

    void Initialize();

    void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                              const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world) override;

    void BufferMaterialUniforms() override;

    glm::vec3 mainColor = glm::vec3(1);
    glm::vec3 specularColor = glm::vec3(1);

    float shininess = 16;
    float ambientIntensity = 0.1f;
    float emissionScale = 1;

    Texture* diffuseTexture = nullptr;
    Texture* specularTexture = nullptr;
    Texture* emissionTexture = nullptr;

private:

    const static int MAX_DIR_LIGHT_COUNT = 20;
    const static int MAX_POINT_LIGHT_COUNT = 20;
    const static int MAX_SPOT_LIGHT_COUNT = 20;

    GLint m_uProjectionMatrix = 0;
    GLint m_uViewMatrix = 0;
    GLint m_uModelMatrix = 0;

    GLint m_uMainColor = 0;
    GLint m_uAmbientIntensity;
    GLint m_uShininess;
    GLint m_uSpecularColor;
    GLint m_uViewPos;

    GLint m_uDiffuseTexture;
    GLint m_uSpecularTexture;
    GLint m_uEmissionTexture;
    GLint m_uEmissionScale;


    struct DirLightUniformLocations
    {
        GLint m_uLightDir;
        GLint m_uLightColor;
        GLint m_uLightIntensity;
    };

    struct PointLightUniformLocations
    {
        GLint m_uLightPosition;
        GLint m_uLightColor;

        GLint m_uLightConstant;
        GLint m_uLightLinear;
        GLint m_uLightQuadratic;

        GLint m_uLightIntensity;
    };

    struct SpotLightUniformLocations
    {
        GLint m_uLightPosition;
        GLint m_uLightDirection;
        GLint m_uLightColor;

        GLint m_uLightCutoff;
        GLint m_uLightOuterCutoff;

        GLint m_uLightConstant;
        GLint m_uLightLinear;
        GLint m_uLightQuadratic;

        GLint m_uLightIntensity;

    };

    GLint m_uActiveDirLights;
    GLint m_uActivePointLights;
    GLint m_uActiveSpotLights;

    GLint m_uFogDensity;
    GLint m_uFogGradient;
    GLint m_uFogColor;

    Texture* m_whiteTexture = nullptr;
    Texture* m_blackTexture = nullptr;

    ResourceManager* m_resourceManager = nullptr;

    std::array<DirLightUniformLocations,MAX_DIR_LIGHT_COUNT> m_dirLightsUniforms;
    std::array<PointLightUniformLocations,MAX_POINT_LIGHT_COUNT> m_pointLightsUniforms;
    std::array<SpotLightUniformLocations,MAX_SPOT_LIGHT_COUNT> m_spotLightsUniforms;

};


#endif //CROW_TEXTUREMATERIAL_H
