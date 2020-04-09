//
// Created by Igli milaqi on 15/03/2020.
//

#ifndef CROW_COLORMATERIAL_H
#define CROW_COLORMATERIAL_H

#include "../AbstractMaterial.h"

class ColorMaterial :public AbstractMaterial {

public:
    ColorMaterial();

    void BufferUniforms(const glm::mat4 &pModelMatrix, const glm::mat4 &pViewMatrix, const glm::mat4 &pProjectionMatrix,
                        const glm::vec3 &viewPos, World *world) override;
    void Initialize();

    glm::vec3 mainColor = glm::vec3(1);
    glm::vec3 specularColor = glm::vec3(1);

    float shininess = 16;
    float ambientIntensity = 0.1f;

private:

    const static int MAX_DIR_LIGHT_COUNT = 10;
    const static int MAX_POINT_LIGHT_COUNT = 10;
    const static int MAX_SPOT_LIGHT_COUNT = 10;

    GLint m_uProjectionMatrix = 0;
    GLint m_uViewMatrix = 0;
    GLint m_uModelMatrix = 0;

    GLint m_uMainColor = 0;
    GLint m_uAmbientIntensity;
    GLint m_uShininess;
    GLint m_uSpecularColor;
    GLint m_uViewPos;


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

    std::array<DirLightUniformLocations,MAX_DIR_LIGHT_COUNT> m_dirLightsUniforms;
    std::array<PointLightUniformLocations,MAX_POINT_LIGHT_COUNT> m_pointLightsUniforms;
    std::array<SpotLightUniformLocations,MAX_SPOT_LIGHT_COUNT> m_spotLightsUniforms;
};


#endif //CROW_COLORMATERIAL_H
