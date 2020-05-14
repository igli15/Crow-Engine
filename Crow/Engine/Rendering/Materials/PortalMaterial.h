//
// Created by Igli milaqi on 14/05/2020.
//

#ifndef CROW_PORTALMATERIAL_H
#define CROW_PORTALMATERIAL_H


#include "../AbstractMaterial.h"

class PortalMaterial : public AbstractMaterial
{

public:

    PortalMaterial();

    void Initialize();

    void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                              const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world) override;

    void BufferMaterialUniforms() override;

    glm::vec3 mainColor = {1,1,1};

private:
    GLint  m_uMainColor,m_uViewMatrix,m_uProjectionMatrix,m_uTime;
};


#endif //CROW_PORTALMATERIAL_H
