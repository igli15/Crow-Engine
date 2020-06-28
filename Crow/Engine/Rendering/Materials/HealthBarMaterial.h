//
// Created by Igli milaqi on 05/06/2020.
//

#ifndef CROW_HEALTHBARMATERIAL_H
#define CROW_HEALTHBARMATERIAL_H


#include "../AbstractMaterial.h"
#include "../Texture.h"

class HealthBarMaterial : public AbstractMaterial
{
public:
    HealthBarMaterial();

    void Initialize();

    void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                              const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world) override;

    void BufferMaterialUniforms() override;

    void BufferModelUniform(const glm::mat4 &pModelMatrix) override;

    glm::vec3 fillColor = glm::vec3(1.0f);
    glm::vec3 emptyColor = glm::vec3(0.1f);

    Texture* noiseMap = nullptr;

    float fillAmount = 1.0f;

private:

    GLint m_uFilledColor,m_uProjection,m_uModel,m_uFillAmount,m_uNoiseMap,m_uEmptyColor,m_uTime;

};


#endif //CROW_HEALTHBARMATERIAL_H
