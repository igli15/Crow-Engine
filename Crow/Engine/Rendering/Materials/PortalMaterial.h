//
// Created by Igli milaqi on 14/05/2020.
//

#ifndef CROW_PORTALMATERIAL_H
#define CROW_PORTALMATERIAL_H


#include "../AbstractMaterial.h"
#include "../Texture.h"

class PortalMaterial : public AbstractMaterial
{

public:

    PortalMaterial();

    void Initialize();

    void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                              const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world) override;

    void BufferMaterialUniforms() override;

    glm::vec3 mainColor = {1,1,1};
    glm::vec3 secondColor = {1,1,1};
    Texture* noiseTexture = nullptr;
    Texture* rotationMaskTexture = nullptr;
    Texture* portalGlowMask = nullptr;

private:
    GLint  m_uMainColor,m_uSecondColor,m_uViewMatrix,m_uProjectionMatrix,m_uTime,m_uNoiseTex,m_uRotationMask,m_uGlowMask;
};


#endif //CROW_PORTALMATERIAL_H
