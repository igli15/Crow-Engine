//
// Created by Igli milaqi on 05/06/2020.
//

#ifndef CROW_HEALTHBARMATERIAL_H
#define CROW_HEALTHBARMATERIAL_H


#include "../AbstractMaterial.h"

class HealthBarMaterial : public AbstractMaterial
{
public:
    HealthBarMaterial();

    void Initialize();

    void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                              const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world) override;

    void BufferMaterialUniforms() override;

    void BufferModelUniform(const glm::mat4 &pModelMatrix) override;

    glm::vec3 color = glm::vec3(1.0f);

    float fillAmount = 1.0f;

private:

    GLint m_uSpriteColor,m_uProjection,m_uModel,m_uFillAmount;

};


#endif //CROW_HEALTHBARMATERIAL_H
