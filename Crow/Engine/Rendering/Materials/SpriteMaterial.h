//
// Created by Igli milaqi on 05/04/2020.
//

#ifndef CROW_SPRITEMATERIAL_H
#define CROW_SPRITEMATERIAL_H


#include "glm/glm.hpp"
#include "../AbstractMaterial.h"

class SpriteInfo;
class Shader;

class SpriteMaterial : public AbstractMaterial
{
public:
    SpriteMaterial();

    void Initialize();

    void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                                      const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world) override;

    void BufferMaterialUniforms() override;

    void BufferModelUniform(const glm::mat4 &pModelMatrix) override;

    glm::vec3 color = glm::vec3(1);


    GLint m_uSpriteColor,m_uProjection,m_uModel;

private:
    glm::mat4 m_orthoProjection = glm::mat4(1);

};


#endif //CROW_SPRITEMATERIAL_H
