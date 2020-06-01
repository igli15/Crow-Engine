//
// Created by Igli milaqi on 11/05/2020.
//

#ifndef CROW_WATERMATERIAL_H
#define CROW_WATERMATERIAL_H


#include "../AbstractMaterial.h"

class Texture;

class WaterMaterial : public AbstractMaterial
{

public:

    WaterMaterial();

    void Initialize();

    void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                              const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world) override;

    void BufferMaterialUniforms() override;

    glm::vec3 mainColor = glm::vec3(0.18f, 0.32f, 0.45f);
    glm::vec3 foamColor = glm::vec3(0.3f, 0.3f, 0.3f);

    float noiseScale = 0.86f;
    float distanceScale = 0.07f;
    float noiseSpeed = 0.03f;
    float causticSpeed = 0.05f;

    Texture* waveNoiseTexture = nullptr;
    Texture* depthGradientTexture = nullptr;
    Texture* foamGradientTexture = nullptr;
    Texture* causticsTexture = nullptr;

private:
    GLint  m_uMainColor,m_uViewMatrix,m_uProjectionMatrix,m_uWaveNoiseTexture,m_uDepthGradientTexture,m_uFoamTexture,m_uCausticsTexture;
    GLint  m_uTime,m_uNoiseScale,m_uDistanceScale,m_uNoiseSpeed,m_uCausticSpeed,m_uFoamColor;
    GLint m_uFogDensity;
    GLint m_uFogGradient;
    GLint m_uViewPos;
};


#endif //CROW_WATERMATERIAL_H
