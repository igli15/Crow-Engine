//
// Created by Igli milaqi on 15/05/2020.
//

#ifndef CROW_UNLITMATERIAL_H
#define CROW_UNLITMATERIAL_H


#include "../AbstractMaterial.h"
#include "../Texture.h"

class UnlitMaterial : public AbstractMaterial
{
public:
    UnlitMaterial();

    void Initialize();

    void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                              const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world) override;

    void BufferMaterialUniforms() override;

    glm::vec3 mainColor = {1,1,1};
    Texture* diffuseTexture = nullptr;

private:
    GLint m_uMainColor,m_uViewMatrix,m_uProjectionMatrix,m_uDiffuseTexture;
};


#endif //CROW_UNLITMATERIAL_H
